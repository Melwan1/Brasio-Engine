#include <renderer/vulkan/vulkan-renderer.hh>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include <io/debug/vulkan-renderer-debug-printer.hh>
#include <io/logging/logger.hh>
#include <geometry/vertex.hh>

#include <renderer/vulkan/builders/all.hh>

#include <shaders/shader-module.hh>

#define MAX_FRAMES_IN_FLIGHT 2
#define CLEAR_COLOR                                                            \
    {                                                                          \
        0.4f, 0.6f, 1.0f, 1.0f                                                 \
    }

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
    vkDestroyBuffer(_logicalDevice->getHandle(), _indexBuffer, nullptr);
    vkFreeMemory(_logicalDevice->getHandle(), _indexBufferMemory, nullptr);
    vkDestroyBuffer(_logicalDevice->getHandle(), _vertexBuffer, nullptr);
    vkFreeMemory(_logicalDevice->getHandle(), _vertexBufferMemory, nullptr);

    vkDestroyPipeline(_logicalDevice->getHandle(), _graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(_logicalDevice->getHandle(), _pipelineLayout,
                            nullptr);
    _renderPass.reset();
    _syncObjects.reset();

    vkDestroyCommandPool(_logicalDevice->getHandle(), _commandPool, nullptr);
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
    ShaderModule vertModule =
        ShaderModule(_logicalDevice->getHandle(),
                     _shaderManager.createShaderModuleFromPath(
                         _logicalDevice->getHandle(),
                         "shaders/vertex/minimal-triangle.vert"));
    ShaderModule fragModule =
        ShaderModule(_logicalDevice->getHandle(),
                     _shaderManager.createShaderModuleFromPath(
                         _logicalDevice->getHandle(),
                         "shaders/fragment/minimal-triangle.frag"));

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertModule.getHandle();
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragModule.getHandle();
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo,
                                                       fragShaderStageInfo };
    std::vector<VkDynamicState> dynamicStates = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
    };

    VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo{};
    dynamicStateCreateInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicStateCreateInfo.dynamicStateCount =
        static_cast<uint32_t>(dynamicStates.size());
    dynamicStateCreateInfo.pDynamicStates = dynamicStates.data();

    auto bindingDescription = Vertex::getBindingDescription();
    auto attributeDescriptions = Vertex::getAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo{};
    vertexInputStateCreateInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
    vertexInputStateCreateInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputStateCreateInfo.vertexAttributeDescriptionCount =
        static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputStateCreateInfo.pVertexAttributeDescriptions =
        attributeDescriptions.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo{};
    inputAssemblyStateCreateInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.scissorCount = 1;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType =
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f;
    rasterizer.depthBiasClamp = 0.0f;
    rasterizer.depthBiasSlopeFactor = 0.0f;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType =
        VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f;
    multisampling.pSampleMask = nullptr;
    multisampling.alphaToCoverageEnable = VK_FALSE;
    multisampling.alphaToOneEnable = VK_FALSE;

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT
        | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT
        | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType =
        VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    for (int i = 0; i < 4; i++)
    {
        colorBlending.blendConstants[i] = 0.0f;
    }

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
    pipelineLayoutCreateInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutCreateInfo.setLayoutCount = 0;
    pipelineLayoutCreateInfo.pSetLayouts = nullptr;
    pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
    pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;

    if (vkCreatePipelineLayout(_logicalDevice->getHandle(),
                               &pipelineLayoutCreateInfo, nullptr,
                               &_pipelineLayout)
        != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create pipeline layout.");
    }

    VkGraphicsPipelineCreateInfo pipelineCreateInfo{};
    pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineCreateInfo.stageCount = 2;
    pipelineCreateInfo.pStages = shaderStages;

    pipelineCreateInfo.pVertexInputState = &vertexInputStateCreateInfo;
    pipelineCreateInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;
    pipelineCreateInfo.pViewportState = &viewportState;
    pipelineCreateInfo.pRasterizationState = &rasterizer;
    pipelineCreateInfo.pMultisampleState = &multisampling;
    pipelineCreateInfo.pDepthStencilState = nullptr;
    pipelineCreateInfo.pColorBlendState = &colorBlending;
    pipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;

    pipelineCreateInfo.layout = _pipelineLayout;
    pipelineCreateInfo.renderPass = _renderPass->getHandle();
    pipelineCreateInfo.subpass = 0;

    pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineCreateInfo.basePipelineIndex = -1;

    uint32_t pipelineCreateInfoCount = 1;
    if (vkCreateGraphicsPipelines(_logicalDevice->getHandle(), VK_NULL_HANDLE,
                                  pipelineCreateInfoCount, &pipelineCreateInfo,
                                  nullptr, &_graphicsPipeline)
        != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create graphics pipeline.");
    }
}

void VulkanRenderer::createCommandPool()
{
    QueueFamilyIndices queueFamilyIndices =
        _physicalDevice->findQueueFamilies();

    VkCommandPoolCreateInfo poolCreateInfo{};
    poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolCreateInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(_logicalDevice->getHandle(), &poolCreateInfo,
                            nullptr, &_commandPool)
        != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create command pool.");
    }
}

void VulkanRenderer::createCommandBuffers()
{
    _commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    VkCommandBufferAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.commandPool = _commandPool;
    allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocateInfo.commandBufferCount =
        static_cast<uint32_t>(_commandBuffers.size());

    if (vkAllocateCommandBuffers(_logicalDevice->getHandle(), &allocateInfo,
                                 _commandBuffers.data())
        != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate command buffers.");
    }
}

void VulkanRenderer::recordCommandBuffer(VkCommandBuffer commandBuffer,
                                         uint32_t imageIndex)
{
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;
    beginInfo.pInheritanceInfo = nullptr;

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to begin recording command buffer.");
    }

    VkRenderPassBeginInfo renderPassBeginInfo{};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.renderPass = _renderPass->getHandle();
    renderPassBeginInfo.framebuffer = _swapchain->framebufferAt(imageIndex);
    renderPassBeginInfo.renderArea.offset = { 0, 0 };
    renderPassBeginInfo.renderArea.extent = _swapchain->getExtent();

    VkClearValue clearColor = { { CLEAR_COLOR } };
    renderPassBeginInfo.clearValueCount = 1;
    renderPassBeginInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo,
                         VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                      _graphicsPipeline);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(_swapchain->getExtent().width);
    viewport.height = static_cast<float>(_swapchain->getExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = _swapchain->getExtent();
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    VkBuffer vertexBuffers[] = { _vertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    uint32_t firstBinding = 0;
    uint32_t bindingCount = 1;
    vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount,
                           vertexBuffers, offsets);
    vkCmdBindIndexBuffer(commandBuffer, _indexBuffer, 0, VK_INDEX_TYPE_UINT16);
    uint32_t instanceCount = 1;
    uint32_t firstVertex = 0;
    uint32_t firstInstance = 0;
    uint32_t instanceOffset = 0;
    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(_indices.size()),
                     instanceCount, firstVertex, firstInstance, instanceOffset);
    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to record command buffer.");
    }
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
    vkResetCommandBuffer(_commandBuffers[_currentFrame], 0);
    recordCommandBuffer(_commandBuffers[_currentFrame], imageIndex);

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
    submitInfo.pCommandBuffers = &_commandBuffers[_currentFrame];

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

void VulkanRenderer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                                  VkMemoryPropertyFlags properties,
                                  VkBuffer &buffer,
                                  VkDeviceMemory &bufferMemory)
{
    VkBufferCreateInfo bufferCreateInfo{};
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.size = size;
    bufferCreateInfo.usage = usage;
    bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(_logicalDevice->getHandle(), &bufferCreateInfo, nullptr,
                       &buffer)
        != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create vertex buffer.");
    }

    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(_logicalDevice->getHandle(), buffer,
                                  &memoryRequirements);

    VkMemoryAllocateInfo memoryAllocateInfo{};
    memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memoryAllocateInfo.allocationSize = memoryRequirements.size;
    memoryAllocateInfo.memoryTypeIndex =
        findMemoryType(memoryRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(_logicalDevice->getHandle(), &memoryAllocateInfo,
                         nullptr, &bufferMemory)
        != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate vertex buffer memory.");
    }
    vkBindBufferMemory(_logicalDevice->getHandle(), buffer, bufferMemory, 0);
}

void VulkanRenderer::createVertexBuffer()
{
    VkDeviceSize bufferSize = sizeof(_vertices[0]) * _vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    VkBufferUsageFlags stagingBufferUsageFlags =
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    VkMemoryPropertyFlags stagingBufferMemoryFlags =
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
        | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    createBuffer(bufferSize, stagingBufferUsageFlags, stagingBufferMemoryFlags,
                 stagingBuffer, stagingBufferMemory);

    void *data;
    vkMapMemory(_logicalDevice->getHandle(), stagingBufferMemory, 0, bufferSize,
                0, &data);
    memcpy(data, _vertices.data(), static_cast<size_t>(bufferSize));
    vkUnmapMemory(_logicalDevice->getHandle(), stagingBufferMemory);

    VkBufferUsageFlags vertexBufferUsageFlags =
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    VkMemoryPropertyFlags vertexBufferMemoryFlags =
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

    createBuffer(bufferSize, vertexBufferUsageFlags, vertexBufferMemoryFlags,
                 _vertexBuffer, _vertexBufferMemory);

    copyBuffer(stagingBuffer, _vertexBuffer, bufferSize);

    vkDestroyBuffer(_logicalDevice->getHandle(), stagingBuffer, nullptr);
    vkFreeMemory(_logicalDevice->getHandle(), stagingBufferMemory, nullptr);
}

void VulkanRenderer::createIndexBuffer()
{
    VkDeviceSize bufferSize = sizeof(_indices[0]) * _indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    VkBufferUsageFlags stagingBufferUsageFlags =
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    VkMemoryPropertyFlags stagingBufferMemoryFlags =
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
        | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    createBuffer(bufferSize, stagingBufferUsageFlags, stagingBufferMemoryFlags,
                 stagingBuffer, stagingBufferMemory);

    void *data;
    vkMapMemory(_logicalDevice->getHandle(), stagingBufferMemory, 0, bufferSize,
                0, &data);
    memcpy(data, _indices.data(), static_cast<size_t>(bufferSize));
    vkUnmapMemory(_logicalDevice->getHandle(), stagingBufferMemory);

    VkBufferUsageFlags indexBufferUsageFlags =
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    VkMemoryPropertyFlags indexBufferMemoryFlags =
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

    createBuffer(bufferSize, indexBufferUsageFlags, indexBufferMemoryFlags,
                 _indexBuffer, _indexBufferMemory);

    copyBuffer(stagingBuffer, _indexBuffer, bufferSize);

    vkDestroyBuffer(_logicalDevice->getHandle(), stagingBuffer, nullptr);
    vkFreeMemory(_logicalDevice->getHandle(), stagingBufferMemory, nullptr);
}

uint32_t VulkanRenderer::findMemoryType(uint32_t typeFilter,
                                        VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(_physicalDevice->getHandle(),
                                        &memoryProperties);

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i))
            && (memoryProperties.memoryTypes[i].propertyFlags & properties)
                == properties)
        {
            return i;
        }
    }

    throw std::runtime_error("Failed to find a suitable memory type.");
}

void VulkanRenderer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer,
                                VkDeviceSize size)
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = _commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(_logicalDevice->getHandle(), &allocInfo,
                             &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkBufferCopy copyRegion;
    copyRegion.srcOffset = 0;
    copyRegion.dstOffset = 0;
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(_logicalDevice->getGraphicsQueue(), 1, &submitInfo,
                  VK_NULL_HANDLE);
    vkQueueWaitIdle(_logicalDevice->getGraphicsQueue());

    vkFreeCommandBuffers(_logicalDevice->getHandle(), _commandPool, 1,
                         &commandBuffer);
}
