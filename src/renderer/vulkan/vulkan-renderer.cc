#include <renderer/vulkan/vulkan-renderer.hh>

#include <renderer/vulkan/builders/command-buffer-array-builder.hh>
#include <renderer/vulkan/builders/command-pool-builder.hh>
#include <renderer/vulkan/builders/depth-attachment-builder.hh>
#include <renderer/vulkan/builders/image-attachment-builder.hh>
#include <renderer/vulkan/builders/instance-builder.hh>
#include <renderer/vulkan/builders/logical-device-builder.hh>
#include <renderer/vulkan/builders/physical-device-builder.hh>
#include <renderer/vulkan/builders/render-pass-builder.hh>
#include <renderer/vulkan/builders/subpass-dependency-builder.hh>
#include <renderer/vulkan/builders/subpass-description-builder.hh>
#include <renderer/vulkan/builders/surface-builder.hh>
#include <renderer/vulkan/builders/swapchain-builder.hh>

#include <utility>
#include <vector>

#define MAX_FRAMES_IN_FLIGHT 2

namespace brasio::renderer::vulkan
{
    VulkanRenderer::VulkanRenderer(GLFWwindow *window, const YAML::Node &config)
        : _window(window)
        , _shaderManager("shaders", "output.log")
    {
        BRASIO_LOG_TRACE("Creating Vulkan renderer", { "CREATE" });
        _maxFramesInFlight = config["max_frames_in_flight"].as<unsigned>();
        _instance = builders::InstanceBuilder(*this)
#ifdef BRASIO_ENABLE_VALIDATION_LAYERS
                        .withValidationLayers({ "VK_LAYER_KHRONOS_validation" })
#endif
                        .build();
        _surface = builders::SurfaceBuilder(*this).build();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain(config["swapchain"]);
        _shaderManager.compileAllShaders();
        createCommandPool();
        for (const YAML::Node &pipelineConfig : config["pipelines"])
        {
            if (!pipelineConfig["type"].as<std::string>().compare("GRAPHICS")
                && pipelineConfig["multisampling"]["rasterization_samples"])
            {
                _msaaSamples = static_cast<VkSampleCountFlagBits>(
                    pipelineConfig["multisampling"]["rasterization_samples"].as<unsigned>());
                break;
            }
        }

        createColorResources();
        createDepthResources();
        createRenderPass();
        _swapchain->createFramebuffers(framebufferAttachmentViews());
        createCommandBuffers();
        createSyncObjects();
        BRASIO_LOG_TRACE("Created Vulkan renderer", { "CREATE" });
    }

    void VulkanRenderer::init()
    {}

    VulkanRenderer::~VulkanRenderer()
    {
        BRASIO_LOG_TRACE("Destroying Vulkan renderer", { "DESTROY" });
        cleanupSwapChain();
        _renderPass.reset();
        _depthAttachment.reset();
        _colorAttachment.reset();
        _syncObjects.reset();

        BRASIO_LOG_TRACE("Destroyed Vulkan renderer", { "DESTROY" });
    }

    void VulkanRenderer::pickPhysicalDevice()
    {
        _physicalDevice = builders::PhysicalDeviceBuilder(*this)
                              .withDeviceExtensions({ VK_KHR_SWAPCHAIN_EXTENSION_NAME })
                              .build();
        _msaaSamples = _physicalDevice->getMaxUsableSampleCount();
    }

    void VulkanRenderer::createLogicalDevice()
    {
        _logicalDevice = builders::LogicalDeviceBuilder(*this).build();
    }

    void VulkanRenderer::createSwapChain(VkPresentModeKHR presentMode)
    {
        _swapchain = builders::SwapchainBuilder(*this)
                         .withSurfaceFormat({ .format = VK_FORMAT_R8G8B8A8_SRGB,
                                              .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR })
                         .withPresentMode(presentMode)
                         .build();
    }

    void VulkanRenderer::createSwapChain()
    {
        createSwapChain(VK_PRESENT_MODE_FIFO_KHR);
    }

    void VulkanRenderer::createSwapChain(const YAML::Node &config)
    {
        std::map<std::string, VkPresentModeKHR> presentModeMap = {
            { "FIFO", VK_PRESENT_MODE_FIFO_KHR }, { "MAILBOX", VK_PRESENT_MODE_MAILBOX_KHR }
        };
        createSwapChain(presentModeMap.at(config["present_mode"].as<std::string>()));
    }

    void VulkanRenderer::createRenderPass()
    {
        VkSubpassDependency dependency =
            builders::SubpassDependencyBuilder()
                .withSrcStageMask(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
                                  | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT)
                .withSrcAccessMask(VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
                                   | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT)
                .withDstStageMask(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
                                  | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT)
                .withDstAccessMask(VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
                                   | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT)
                .build();

        VkAttachmentDescription depthAttachmentDescription =
            _depthAttachment->getAttachmentDescription();

        if (!isMultisampled())
        {
            VkAttachmentReference depthAttachmentReference =
                _depthAttachment->getAttachmentReference(0);
            VkAttachmentDescription colorAttachmentDescription =
                ImageAttachment::sGetAttachmentDescription(_swapchain->getFormat());
            VkAttachmentReference colorAttachmentReference =
                ImageAttachment::sGetAttachmentReference(1);
            builders::SubpassDescriptionBuilder subpassBuilder =
                builders::SubpassDescriptionBuilder()
                    .withAdditionalAttachment(colorAttachmentDescription, colorAttachmentReference)
                    .withAdditionalAttachment(depthAttachmentDescription, depthAttachmentReference);
            VkSubpassDescription subpass = subpassBuilder.build();

            _renderPass = builders::RenderPassBuilder(*this)
                              .withAdditionalAttachmentDescription(depthAttachmentDescription)
                              .withAdditionalAttachmentDescription(colorAttachmentDescription)
                              .withAdditionalSubpass(subpass)
                              .withAdditionalSubpassDependency(dependency)
                              .build();
            return;
        }

        VkAttachmentDescription colorAttachmentDescription =
            _colorAttachment->getAttachmentDescription();
        VkAttachmentReference colorAttachmentReference =
            _colorAttachment->getAttachmentReference(0);
        VkAttachmentReference depthAttachmentReference =
            _depthAttachment->getAttachmentReference(1);
        VkAttachmentDescription colorAttachmentResolveDescription =
            ImageAttachment::sGetAttachmentDescription(_swapchain->getFormat());
        VkAttachmentReference colorAttachmentResolveReference =
            ImageAttachment::sGetAttachmentReference(2);
        builders::SubpassDescriptionBuilder subpassBuilder =
            builders::SubpassDescriptionBuilder()
                .withAdditionalAttachment(colorAttachmentDescription, colorAttachmentReference)
                .withAdditionalAttachment(depthAttachmentDescription, depthAttachmentReference)
                .withAdditionalResolveAttachment(colorAttachmentResolveReference);
        VkSubpassDescription subpass = subpassBuilder.build();

        _renderPass = builders::RenderPassBuilder(*this)
                          .withAdditionalAttachmentDescription(colorAttachmentDescription)
                          .withAdditionalAttachmentDescription(depthAttachmentDescription)
                          .withAdditionalAttachmentDescription(colorAttachmentResolveDescription)
                          .withAdditionalSubpass(subpass)
                          .withAdditionalSubpassDependency(dependency)
                          .build();
    }

    void VulkanRenderer::createCommandPool()
    {
        QueueFamilyIndices queueFamilyIndices = _physicalDevice->findQueueFamilies();

        _commandPool = builders::CommandPoolBuilder(*this)
                           .withQueueFamilyIndex(queueFamilyIndices.graphicsComputeFamily.value())
                           .build();
    }

    void VulkanRenderer::createCommandBuffers()
    {
        builders::CommandBufferArrayBuilder commandBufferArrayBuilder(*this);
        commandBufferArrayBuilder.withLevel(VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            .withCommandBufferCount(MAX_FRAMES_IN_FLIGHT * 2); // graphics and compute
        _commandBuffers = commandBufferArrayBuilder.build();
    }

    void VulkanRenderer::createSyncObjects()
    {
        VkSemaphoreCreateInfo semaphoreCreateInfo{};
        semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceCreateInfo{};
        fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
        _syncObjects = std::make_unique<SyncObjects>(
            *this, 2 * _maxFramesInFlight + _swapchain->getImageCount(), 2 * _maxFramesInFlight,
            semaphoreCreateInfo, fenceCreateInfo);
    }

    void VulkanRenderer::deferFreeTexture(TextureType texture) const
    {
        _pendingTextureFrees.push_back(
            { std::move(texture), _frameCounter + 2 * _maxFramesInFlight });
    }

    void VulkanRenderer::drawFrame(Renderable &root)
    {
        BRASIO_LOG_TRACE("Starting frame render", { "RENDER" });
        std::erase_if(_pendingTextureFrees, [this](const PendingTextureFree &pending) {
            return _frameCounter >= pending.freeAtFrame;
        });
        _syncObjects->waitSingleFence(_currentFrame);
        BRASIO_LOG_TRACE("fence waited for", { "RENDER" });

        BRASIO_LOG_TRACE("acquiring next image", { "RENDER" });

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(
            _logicalDevice->getHandle(), _swapchain->getHandle(), UINT64_MAX,
            _syncObjects->semaphoreAt(_currentFrame), VK_NULL_HANDLE, &imageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR)
        {
            recreateSwapChain();
            return;
        }

        else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
        {
            BRASIO_LOG_CRITICAL("Failed to acquire swapchain image.", { "RENDER" });
        }

        BRASIO_LOG_TRACE("acquired next image", { "RENDER" });

        _syncObjects->resetSingleFence(_currentFrame);
        _commandBuffers->reset(_currentFrame);
        _commandBuffers->record(_currentFrame, imageIndex, root);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { _syncObjects->semaphoreAt(_currentFrame) };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &_commandBuffers->at(_currentFrame);

        VkSemaphore signalSemaphores[] = { _syncObjects->semaphoreAt(MAX_FRAMES_IN_FLIGHT
                                                                     + imageIndex) };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        BRASIO_VULKAN_CHECK(vkQueueSubmit(_logicalDevice->getGraphicsQueue(), 1, &submitInfo,
                                          _syncObjects->fenceAt(_currentFrame)),
                            "submit draw command buffer", { "RENDER" });
        VkSwapchainKHR swapchains[] = { _swapchain->getHandle() };
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapchains;
        presentInfo.pImageIndices = &imageIndex;
        presentInfo.pResults = nullptr;
        result = vkQueuePresentKHR(_logicalDevice->getPresentationQueue(), &presentInfo);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR
            || _resizedFramebuffer)
        {
            _resizedFramebuffer = false;
            recreateSwapChain();
        }
        else if (result != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL("Failed to present swapchain image.", { "RENDER" });
        }

        _currentFrame++;
        _currentFrame %= MAX_FRAMES_IN_FLIGHT;
        _frameCounter++;

        BRASIO_LOG_TRACE("Ending frame render", { "RENDER" });
    }

    void VulkanRenderer::waitIdle() const
    {
        _logicalDevice->waitIdle();
    }

    void VulkanRenderer::cleanupSwapChain()
    {
        _logicalDevice->waitIdle();
        _swapchain.reset();
    }

    void VulkanRenderer::recreateSwapChain()
    {
        int width = 0;
        int height = 0;
        glfwGetFramebufferSize(_window, &width, &height);
        while (width == 0 || height == 0)
        {
            glfwGetFramebufferSize(_window, &width, &height);
            glfwWaitEvents();
        }
        VkPresentModeKHR presentMode = _swapchain->getPresentMode();
        cleanupSwapChain();
        createSwapChain(presentMode);
        createColorResources();
        createDepthResources();
        _swapchain->createFramebuffers(framebufferAttachmentViews());
    }

    void VulkanRenderer::createDepthResources()
    {
        VkExtent2D swapchainExtent = _swapchain->getExtent();
        _depthAttachment = builders::DepthAttachmentBuilder(*this)
                               .withExtent(swapchainExtent.width, swapchainExtent.height)
                               .withSamples(_msaaSamples)
                               .withFormat(_physicalDevice->findDepthFormat())
                               .build();
    }

    void VulkanRenderer::createColorResources()
    {
        if (!isMultisampled())
        {
            _colorAttachment.reset();
            return;
        }
        VkFormat swapchainFormat = _swapchain->getFormat();
        VkExtent2D swapchainExtent = _swapchain->getExtent();
        _colorAttachment = builders::ImageAttachmentBuilder(*this)
                               .withExtent(swapchainExtent.width, swapchainExtent.height)
                               .withSamples(_msaaSamples)
                               .withFormat(swapchainFormat)
                               .build();
    }

    bool VulkanRenderer::isMultisampled() const
    {
        return _msaaSamples != VK_SAMPLE_COUNT_1_BIT;
    }

    std::vector<VkImageView> VulkanRenderer::framebufferAttachmentViews() const
    {
        if (isMultisampled())
        {
            return { _colorAttachment->getImageView(), _depthAttachment->getImageView() };
        }
        return { _depthAttachment->getImageView() };
    }

    GLFWwindow *VulkanRenderer::getWindow() const
    {
        return _window;
    }

    const VkInstance &VulkanRenderer::getInstance() const
    {
        return _instance->getHandle();
    }

    const VkSurfaceKHR &VulkanRenderer::getSurface() const
    {
        return _surface->getHandle();
    }

    const VkPhysicalDevice &VulkanRenderer::getPhysicalDevice() const
    {
        return _physicalDevice->getHandle();
    }

    const PhysicalDevice &VulkanRenderer::getPhysicalDeviceWrapper() const
    {
        return *_physicalDevice;
    }

    const VkDevice &VulkanRenderer::getLogicalDevice() const
    {
        return _logicalDevice->getHandle();
    }

    const LogicalDevice &VulkanRenderer::getLogicalDeviceWrapper() const
    {
        return *_logicalDevice;
    }

    const Swapchain &VulkanRenderer::getSwapchain() const
    {
        return *_swapchain;
    }

    const VkCommandPool &VulkanRenderer::getCommandPool() const
    {
        return _commandPool->getHandle();
    }

    const VkRenderPass &VulkanRenderer::getRenderPass() const
    {
        return _renderPass->getHandle();
    }

    const RenderPass &VulkanRenderer::getRenderPassWrapper() const
    {
        return *_renderPass;
    }

    const CommandBufferArrayType &VulkanRenderer::getCommandBuffers() const
    {
        return _commandBuffers;
    }

    unsigned VulkanRenderer::getMaxFramesInFlight() const
    {
        return _maxFramesInFlight;
    }

    uint32_t VulkanRenderer::getCurrentFrame() const
    {
        return _currentFrame;
    }

    const shaders::ShaderManager &VulkanRenderer::getShaderManager() const
    {
        return _shaderManager;
    }

    VulkanRendererType VulkanRenderer::fromConfig(const YAML::Node &config, GLFWwindow *window)
    {
        return std::make_unique<VulkanRenderer>(window, config);
    }
} // namespace brasio::renderer::vulkan
