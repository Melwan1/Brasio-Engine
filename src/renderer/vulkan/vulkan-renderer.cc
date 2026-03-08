#include <renderer/vulkan/vulkan-renderer.hh>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include <io/debug/vulkan-renderer-debug-printer.hh>
#include <io/logging/logger.hh>
#include <geometry/vertex.hh>

#include <renderer/vulkan/builders/all.hh>

#include <shaders/shader-module.hh>

#define MAX_FRAMES_IN_FLIGHT 2

VulkanRenderer::VulkanRenderer(GLFWwindow *window)
    : _window(window)
    , _shaderManager("shaders", "output.log")
    , _vertices({ { { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
                  { { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
                  { { 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
                  { { -0.5f, 0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f } } })
    , _indices({ 0, 1, 2, 2, 3, 0 })
{
    Logger::trace(std::cout, "Creating Vulkan renderer", { "CREATE" });
    _instance = InstanceBuilder()
                    .withValidationLayers({ "VK_LAYER_KHRONOS_validation" })
                    .build();
    _surface = SurfaceBuilder(_instance->getHandle(), _window).build();
    pickPhysicalDevice();
    createLogicalDevice();
    createSwapChain();
    _shaderManager.compileAllShaders();
    createRenderPass();
    _swapchain->createFramebuffers(_renderPass->getHandle());
    createGraphicsPipeline();
    createCommandPool();
    createVertexBuffer();
    createIndexBuffer();
    createCommandBuffers();
    createSyncObjects();
    Logger::trace(std::cout, "Created Vulkan renderer", { "CREATE" });
}

void VulkanRenderer::init()
{}

VulkanRenderer::~VulkanRenderer()
{
    Logger::trace(std::cout, "Destroying Vulkan renderer", { "DESTROY" });
    cleanupSwapChain();
    _indexBuffer.reset();
    _vertexBuffer.reset();
    _graphicsPipeline.reset();
    _pipelineLayout.reset();
    _renderPass.reset();
    _syncObjects.reset();

    Logger::trace(std::cout, "Destroyed Vulkan renderer", { "DESTROY" });
}

void VulkanRenderer::pickPhysicalDevice()
{
    _physicalDevice =
        PhysicalDeviceBuilder(_instance->getHandle(), _surface->getHandle())
            .withDeviceExtensions({ VK_KHR_SWAPCHAIN_EXTENSION_NAME })
            .build();
}

void VulkanRenderer::createLogicalDevice()
{
    _logicalDevice =
        LogicalDeviceBuilder(*_physicalDevice)
            .withValidationLayers({ "VK_LAYER_KHRONOS_validation" })
            .build();
}

void VulkanRenderer::createSwapChain()
{
    _swapchain =
        SwapchainBuilder(_window, *_physicalDevice, _logicalDevice->getHandle(),
                         _surface->getHandle())
            .withSurfaceFormat(
                { .format = VK_FORMAT_R8G8B8A8_SRGB,
                  .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR })
            .withPresentMode(VK_PRESENT_MODE_MAILBOX_KHR)
            .build();
}

void VulkanRenderer::createRenderPass()
{
    const Attachment attachment(
        AttachmentDescriptionBuilder(_swapchain->getFormat()).build(),
        AttachmentReferenceBuilder().build());
    SubpassDescriptionBuilder subpassBuilder =
        SubpassDescriptionBuilder().withAdditionalAttachment(attachment);
    VkSubpassDescription subpass = subpassBuilder.build();

    VkSubpassDependency dependency = SubpassDependencyBuilder().build();

    RenderPassBuilder builder =
        RenderPassBuilder(_logicalDevice->getHandle())
            .withAdditionalAttachment(attachment)
            .withAdditionalSubpass(subpass)
            .withAdditionalSubpassDependency(dependency);

    _renderPass = builder.build();
}

void VulkanRenderer::createGraphicsPipeline()
{
    std::vector<fs::path> shaders = { "vertex/minimal-triangle.vert",
                                      "fragment/minimal-triangle.frag" };
    _pipelineLayout =
        PipelineLayoutBuilder(_logicalDevice->getHandle()).build();

    GraphicsPipelineBuilder pipelineBuilder(
        _logicalDevice->getHandle(), _shaderManager,
        _pipelineLayout->getHandle(), _renderPass->getHandle());
    pipelineBuilder.withShaders(shaders);
    _graphicsPipeline = pipelineBuilder.build();
}

void VulkanRenderer::createCommandPool()
{
    QueueFamilyIndices queueFamilyIndices =
        _physicalDevice->findQueueFamilies();

    _commandPool =
        CommandPoolBuilder(_logicalDevice->getHandle())
            .withQueueFamilyIndex(queueFamilyIndices.graphicsFamily.value())
            .build();
}

void VulkanRenderer::createCommandBuffers()
{
    CommandBufferArrayBuilder commandBufferArrayBuilder(
        _logicalDevice->getHandle(), _commandPool->getHandle());
    commandBufferArrayBuilder.withLevel(VK_COMMAND_BUFFER_LEVEL_PRIMARY)
        .withCommandBufferCount(MAX_FRAMES_IN_FLIGHT);
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
        _logicalDevice->getHandle(),
        MAX_FRAMES_IN_FLIGHT + _swapchain->getImageCount(),
        MAX_FRAMES_IN_FLIGHT, semaphoreCreateInfo, fenceCreateInfo);
}

void VulkanRenderer::drawFrame()
{
    _syncObjects->waitSingleFence(_currentFrame);

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
        throw std::runtime_error("Failed to acquire swap chain image.");
    }

    _syncObjects->resetSingleFence(_currentFrame);
    vkResetCommandBuffer(_commandBuffers->at(_currentFrame), 0);
    _commandBuffers->record(_currentFrame, imageIndex, _renderPass->getHandle(),
                            _swapchain, _graphicsPipeline,
                            _vertexBuffer->getHandle(),
                            _indexBuffer->getHandle(), _indices);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { _syncObjects->semaphoreAt(_currentFrame) };
    VkPipelineStageFlags waitStages[] = {
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
    };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &_commandBuffers->at(_currentFrame);

    VkSemaphore signalSemaphores[] = { _syncObjects->semaphoreAt(
        MAX_FRAMES_IN_FLIGHT + imageIndex) };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(_logicalDevice->getGraphicsQueue(), 1, &submitInfo,
                      _syncObjects->fenceAt(_currentFrame))
        != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to submit draw command buffer.");
    }

    VkSwapchainKHR swapchains[] = { _swapchain->getHandle() };
    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapchains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr;
    result =
        vkQueuePresentKHR(_logicalDevice->getPresentationQueue(), &presentInfo);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR
        || _resizedFramebuffer)
    {
        _resizedFramebuffer = false;
        recreateSwapChain();
    }
    else if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to present swap chain image.");
    }

    _currentFrame++;
    _currentFrame %= MAX_FRAMES_IN_FLIGHT;
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
    cleanupSwapChain();
    createSwapChain();
    _swapchain->createFramebuffers(_renderPass->getHandle());
}

void VulkanRenderer::createVertexBuffer()
{
    VkDeviceSize bufferSize = sizeof(_vertices[0]) * _vertices.size();

    VkBufferUsageFlags stagingBufferUsageFlags =
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    VkMemoryPropertyFlags stagingBufferMemoryFlags =
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
        | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    BufferBuilder stagingBufferBuilder(_physicalDevice, _logicalDevice);
    stagingBufferBuilder.withSize(bufferSize)
        .withUsage(stagingBufferUsageFlags)
        .withData(_vertices.data())
        .withMemoryProperties(stagingBufferMemoryFlags);

    BufferType stagingBuffer = stagingBufferBuilder.build();

    VkBufferUsageFlags vertexBufferUsageFlags =
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    VkMemoryPropertyFlags vertexBufferMemoryFlags =
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

    BufferBuilder vertexBufferBuilder(_physicalDevice, _logicalDevice);
    vertexBufferBuilder.withSize(bufferSize)
        .withUsage(vertexBufferUsageFlags)
        .withMemoryProperties(vertexBufferMemoryFlags);

    _vertexBuffer = vertexBufferBuilder.build();

    stagingBuffer->copyInto(*_vertexBuffer, _commandPool->getHandle(),
                            bufferSize);
}

void VulkanRenderer::createIndexBuffer()
{
    VkDeviceSize bufferSize = sizeof(_indices[0]) * _indices.size();

    VkBufferUsageFlags stagingBufferUsageFlags =
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    VkMemoryPropertyFlags stagingBufferMemoryFlags =
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
        | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    BufferBuilder stagingBufferBuilder(_physicalDevice, _logicalDevice);
    stagingBufferBuilder.withSize(bufferSize)
        .withUsage(stagingBufferUsageFlags)
        .withMemoryProperties(stagingBufferMemoryFlags);

    BufferType stagingBuffer = stagingBufferBuilder.build();

    VkBufferUsageFlags indexBufferUsageFlags =
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    VkMemoryPropertyFlags indexBufferMemoryFlags =
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

    BufferBuilder indexBufferBuilder(_physicalDevice, _logicalDevice);
    indexBufferBuilder.withSize(bufferSize)
        .withUsage(indexBufferUsageFlags)
        .withMemoryProperties(indexBufferMemoryFlags);

    _indexBuffer = indexBufferBuilder.build();

    stagingBuffer->copyInto(*_indexBuffer, _commandPool->getHandle(),
                            bufferSize);
}
