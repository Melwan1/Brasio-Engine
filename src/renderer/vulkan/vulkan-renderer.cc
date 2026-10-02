#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <random>

#include <renderer/vulkan/vulkan-renderer.hh>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <io/debug/vulkan-renderer-debug-printer.hh>
#include <io/files/obj-parser.hh>
#include <io/logging/logger.hh>
#include <geometry/vertex.hh>
#include <model/model.hh>
#include <renderer/structs/all.hh>

#include <renderer/vulkan/builders/all.hh>

#include <shaders/shader-module.hh>
#include <mesh/fwd.hh>
#include <utils/libutils.hh>

#define MAX_FRAMES_IN_FLIGHT 2
#define PARTICLE_COUNT 8192

namespace brasio::renderer::vulkan
{
    VulkanRenderer::VulkanRenderer(GLFWwindow *window)
        : _window(window)
        , _shaderManager("shaders", "output.log")
        , _maxFramesInFlight(MAX_FRAMES_IN_FLIGHT)
    {
        BRASIO_LOG_TRACE("Creating Vulkan renderer", { "CREATE" });
        _instance = builders::InstanceBuilder(*this)
#ifdef BRASIO_ENABLE_VALIDATION_LAYERS
                        .withValidationLayers({ "VK_LAYER_KHRONOS_validation" })
#endif
                        .build();
        _surface = builders::SurfaceBuilder(*this).build();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        _shaderManager.compileAllShaders();
        createCommandPool();
        io::files::OBJParser objParser("assets/models/viking_room.obj");
        objParser.load();
        model::Model model(objParser);
        _mesh1 = model.toMesh();
        //_mesh1 = std::make_unique<mesh::Sphere>(16, 16);
        //_mesh1->applyTranslation(mesh::TransformMode::CPU,
        //                         { -1.0f, 0.0f, 1.0f });
        _mesh1->createBuffers(*this);

        _mesh2 = model.toMesh();
        //_mesh2 = std::make_unique<mesh::Cone>();
        _mesh2->applyTranslation(mesh::TransformMode::CPU, { 1.0f, 0.0f, -1.0f });
        _mesh2->createBuffers(*this);
        createColorResources();
        createDepthResources();
        createRenderPass();
        _swapchain->createFramebuffers(framebufferAttachmentViews());
        createPipelines();
        createUniformBuffers();
        createTexture();
        createStorageBuffers();
        createDescriptorPool();
        createDescriptorSets();
        createCommandBuffers();
        createSyncObjects();
        BRASIO_LOG_TRACE("Created Vulkan renderer", { "CREATE" });
    }

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
        io::files::OBJParser objParser("assets/models/viking_room.obj");
        objParser.load();
        model::Model model(objParser);
        _mesh1 = model.toMesh();
        _mesh1 = std::make_unique<mesh::Cube>();
        //_mesh1 = std::make_unique<mesh::Sphere>(16, 16);
        //_mesh1->applyTranslation(mesh::TransformMode::CPU,
        //                         { -1.0f, 0.0f, 1.0f });
        _mesh1->createBuffers(*this);

        _mesh2 = model.toMesh();
        //_mesh2 = std::make_unique<mesh::Cone>();
        _mesh2->applyTranslation(mesh::TransformMode::CPU, { 1.0f, 0.0f, -1.0f });
        _mesh2->createBuffers(*this);

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
        createPipelines(config["pipelines"]);
        createUniformBuffers();
        createStorageBuffers();
        createCommandBuffers();
        createSyncObjects();
        BRASIO_LOG_TRACE("Created Vulkan renderer", { "CREATE" });
    }

    void VulkanRenderer::init()
    {
        createDescriptorPool();
        createDescriptorSets();
    }

    VulkanRenderer::~VulkanRenderer()
    {
        BRASIO_LOG_TRACE("Destroying Vulkan renderer", { "DESTROY" });
        cleanupSwapChain();
        _mesh1.reset();
        _mesh2.reset();
        _graphicsDescriptorPool.reset();
        _computeDescriptorPool.reset();
        _textures.clear();
        _storageBuffers.clear();
        _uniformBuffers.clear();
        _computeUniformBuffers.clear();
        _computePipelines.clear();
        _graphicsPipelines.clear();
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

    void VulkanRenderer::createPipelines()
    {
        std::vector<fs::path> shaders = { "vertex/ubo.vert", "fragment/texture.frag" };

        builders::GraphicsPipelineBuilder pipelineBuilder(*this);
        pipelineBuilder.withDescriptorSetLayout(builders::DescriptorSetLayoutBuilder(*this)
                                                    .withUniformBuffers(1)
                                                    .withTextures(1)
                                                    .build());
        pipelineBuilder.withShaders(shaders);
        _graphicsPipelines.emplace_back(pipelineBuilder.build());
    }

    void VulkanRenderer::createPipelines(const YAML::Node &config)
    {
        for (const YAML::Node &pipelineConfig : config)
        {
            builders::DescriptorSetLayoutBindingBuilder::resetIndex();
            if (!pipelineConfig["type"].as<std::string>().compare("GRAPHICS"))
            {
                builders::GraphicsPipelineBuilder pipelineBuilder(*this);
                pipelineBuilder.withDescriptorSetLayout(builders::DescriptorSetLayoutBuilder(*this)
                                                            .withUniformBuffers(1)
                                                            .withTextures(1)
                                                            .build());
                pipelineBuilder.withConfig(pipelineConfig);
                _graphicsPipelines.emplace_back(pipelineBuilder.build());
            }
            else if (!pipelineConfig["type"].as<std::string>().compare("COMPUTE"))
            {
                PipelineLayoutType pipelineLayout =
                    builders::PipelineLayoutBuilder(*this)
                        .withDescriptorSetLayout(
                            builders::DescriptorSetLayoutBuilder(*this)
                                .withUniformBuffers(1, VK_SHADER_STAGE_COMPUTE_BIT)
                                .withStorageBuffers(2)
                                .build())
                        .build();
                _computePipelines.emplace_back(builders::ComputePipelineBuilder(*this)
                                                   .withShader("compute/particles.comp")
                                                   .withPipelineLayout(std::move(pipelineLayout))
                                                   .build());
            }
        }
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

    void VulkanRenderer::drawFrame()
    {
        runCompute();

        BRASIO_LOG_TRACE("Starting frame render", { "RENDER" });
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
        _commandBuffers->record(_currentFrame, imageIndex);

        updateUniformBuffer(_currentFrame);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        uint32_t computeSemaphoreIndex =
            MAX_FRAMES_IN_FLIGHT + _swapchain->getImageCount() + _currentFrame;
        VkSemaphore waitSemaphores[] = { _syncObjects->semaphoreAt(computeSemaphoreIndex),
                                         _syncObjects->semaphoreAt(_currentFrame) };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
                                              VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 2;
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

        BRASIO_LOG_TRACE("Ending frame render", { "RENDER" });
    }

    void VulkanRenderer::runCompute()
    {
        BRASIO_LOG_TRACE("Starting frame compute", { "COMPUTE" });

        uint32_t computeFenceIndex = MAX_FRAMES_IN_FLIGHT + _currentFrame;
        uint32_t computeCommandBufferIndex = MAX_FRAMES_IN_FLIGHT + _currentFrame;
        uint32_t computeSemaphoreIndex =
            MAX_FRAMES_IN_FLIGHT + _swapchain->getImageCount() + _currentFrame;

        _syncObjects->waitSingleFence(computeFenceIndex);

        static auto lastFrameTime = std::chrono::high_resolution_clock::now();
        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        structs::ComputeUniformBufferObject cubo{};
        cubo.deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(
                             currentFrameTime - lastFrameTime)
                             .count();
        lastFrameTime = currentFrameTime;
        _computeUniformBuffers.at(_currentFrame)->setContent(&cubo);

        _syncObjects->resetSingleFence(computeFenceIndex);

        _commandBuffers->reset(computeCommandBufferIndex);
        _commandBuffers->recordCompute(computeCommandBufferIndex, PARTICLE_COUNT / 256);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &_commandBuffers->at(computeCommandBufferIndex);

        VkSemaphore signalSemaphores[] = { _syncObjects->semaphoreAt(computeSemaphoreIndex) };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        BRASIO_VULKAN_CHECK(vkQueueSubmit(_logicalDevice->getComputeQueue(), 1, &submitInfo,
                                          _syncObjects->fenceAt(computeFenceIndex)),
                            "submit compute command buffer", { "COMPUTE" });

        BRASIO_LOG_TRACE("Ending frame compute", { "COMPUTE" });
    }

    void VulkanRenderer::addTexture(TextureType texture)
    {
        _textures.emplace_back(std::move(texture));
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

    void VulkanRenderer::createUniformBuffers()
    {
        VkDeviceSize bufferSize = sizeof(structs::UniformBufferObject);
        for (uint32_t index = 0; index < MAX_FRAMES_IN_FLIGHT; index++)
        {
            _uniformBuffers.emplace_back(
                builders::UniformBufferBuilder(*this).withSize(bufferSize).build());
            _uniformBuffers.back()->mapMemory();
            // persistent mapping for all uniform buffers
        }

        VkDeviceSize computeBufferSize = sizeof(structs::ComputeUniformBufferObject);
        for (uint32_t index = 0; index < MAX_FRAMES_IN_FLIGHT; index++)
        {
            _computeUniformBuffers.emplace_back(
                builders::UniformBufferBuilder(*this).withSize(computeBufferSize).build());
            _computeUniformBuffers.back()->mapMemory();
        }
    }

    void VulkanRenderer::createStorageBuffers()
    {
        std::default_random_engine rndEngine(static_cast<unsigned>(std::time(nullptr)));
        std::uniform_real_distribution<float> rndDist(0.0f, 1.0f);

        std::vector<structs::Particle> particles(PARTICLE_COUNT);

        for (structs::Particle &particle : particles)
        {
            float r = 0.25f * std::sqrt(rndDist(rndEngine));
            float theta = rndDist(rndEngine) * 2 * std::numbers::pi;
            float x = r * std::cos(theta) * _swapchain->getHeight() / _swapchain->getWidth();
            float y = r * std::sin(theta);
            particle.position = glm::vec2(x, y);
            particle.velocity = glm::normalize(glm::vec2(x, y)) * 2.5e-4f;
            particle.color =
                glm::vec4(rndDist(rndEngine), rndDist(rndEngine), rndDist(rndEngine), 1.0f);
        }
        VkDeviceSize bufferSize = sizeof(structs::Particle) * PARTICLE_COUNT;

        BufferType particleStagingBuffer = builders::StagingBufferBuilder(*this)
                                               .withSize(bufferSize)
                                               .withData(particles.data())
                                               .build();
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
        {
            _storageBuffers.emplace_back(
                builders::StorageBufferBuilder(*this).withSize(bufferSize).build());
            particleStagingBuffer->copyInto(*_storageBuffers.back());
        }
    }

    void VulkanRenderer::updateUniformBuffer(uint32_t currentImage)
    {
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time =
            std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime)
                .count();
        (void)time;
        structs::UniformBufferObject ubo{};
        // ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f),
        //                         glm::vec3(0.0f, 0.0f, 1.0f));
        // ubo.model = glm::rotate(ubo.model, time / 2 * glm::radians(90.0f),
        //                         glm::vec3(0.0f, 1.0f, 0.0f));
        // ubo.model = glm::rotate(ubo.model, time / 4 * glm::radians(90.0f),
        //                         glm::vec3(1.0f, 0.0f, 0.0f));
        ubo.model = glm::mat4(1.0f);
        ubo.view = glm::lookAt(glm::vec3(3.0f, 1.5f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.proj = glm::perspective(glm::radians(45.0f),
                                    _swapchain->getWidth() / _swapchain->getHeight(), 0.1f, 10.0f);
        ubo.proj[1][1] *= -1;
        _uniformBuffers.at(currentImage)->setContent(&ubo);
    }

    void VulkanRenderer::createDescriptorPool()
    {
        _graphicsDescriptorPool =
            builders::DescriptorPoolBuilder(*this)
                .withMaxSets(_maxFramesInFlight)
                .withDescriptorPoolSizes(
                    { builders::DescriptorPoolSizeBuilder()
                          .withDescriptorCount(_maxFramesInFlight)
                          .withDescriptorType(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
                          .build(),
                      builders::DescriptorPoolSizeBuilder()
                          .withDescriptorCount(_maxFramesInFlight * _textures.size())
                          .withDescriptorType(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
                          .build() })
                .build();

        _computeDescriptorPool =
            builders::DescriptorPoolBuilder(*this)
                .withMaxSets(_maxFramesInFlight)
                .withDescriptorPoolSizes(
                    { builders::DescriptorPoolSizeBuilder()
                          .withDescriptorCount(_maxFramesInFlight)
                          .withDescriptorType(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
                          .build(),
                      builders::DescriptorPoolSizeBuilder()
                          .withDescriptorCount(_maxFramesInFlight * 2)
                          .withDescriptorType(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER)
                          .build() })
                .build();
    }
    void VulkanRenderer::createDescriptorSets()
    {
        DescriptorSetsType graphicsDescriptorSets =
            builders::DescriptorSetsBuilder(*this, _graphicsDescriptorPool->getHandle())
                .withSetsCount(_maxFramesInFlight)
                .withSetLayout(_graphicsPipelines.at(0)
                                   ->getPipelineLayout()
                                   .getDescriptorSetLayout()
                                   .getHandle())
                .build();
        graphicsDescriptorSets->update(_uniformBuffers, _textures, {});
        _graphicsDescriptorPool->setDescriptorSets(std::move(graphicsDescriptorSets));

        DescriptorSetsType computeDescriptorSets =
            builders::DescriptorSetsBuilder(*this, _computeDescriptorPool->getHandle())
                .withSetsCount(_maxFramesInFlight)
                .withSetLayout(_computePipelines.at(0)
                                   ->getPipelineLayout()
                                   .getDescriptorSetLayout()
                                   .getHandle())
                .build();
        computeDescriptorSets->update(_computeUniformBuffers, {}, _storageBuffers);
        _computeDescriptorPool->setDescriptorSets(std::move(computeDescriptorSets));
    }

    void VulkanRenderer::createTexture()
    {
        _textures.emplace_back(
            builders::TextureBuilder(*this)
                .withTextureImage(images::P3PPM::load("assets/textures/viking_room.ppm"))
                .build());
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

    const std::vector<GraphicsPipelineType> &VulkanRenderer::getGraphicsPipelines() const
    {
        return _graphicsPipelines;
    }

    const std::vector<ComputePipelineType> &VulkanRenderer::getComputePipelines() const
    {
        return _computePipelines;
    }

    const CommandBufferArrayType &VulkanRenderer::getCommandBuffers() const
    {
        return _commandBuffers;
    }

    const mesh::Mesh &VulkanRenderer::getMesh1() const
    {
        return *_mesh1;
    }

    const mesh::Mesh &VulkanRenderer::getMesh2() const
    {
        return *_mesh2;
    }

    const DescriptorSets &VulkanRenderer::getDescriptorSets() const
    {
        return _graphicsDescriptorPool->getDescriptorSets();
    }

    const DescriptorSets &VulkanRenderer::getComputeDescriptorSets() const
    {
        return _computeDescriptorPool->getDescriptorSets();
    }

    uint32_t VulkanRenderer::getCurrentFrame() const
    {
        return _currentFrame;
    }

    const VkBuffer &VulkanRenderer::getParticleVertexBuffer() const
    {
        return _storageBuffers[_currentFrame]->getHandle();
    }

    uint32_t VulkanRenderer::getParticleCount() const
    {
        return PARTICLE_COUNT;
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
