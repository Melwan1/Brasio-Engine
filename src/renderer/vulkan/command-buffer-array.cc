#include <renderer/vulkan/command-buffer-array.hh>

#define CLEAR_COLOR                                                            \
    {                                                                          \
        0.4f, 0.6f, 1.0f, 1.0f                                                 \
    }

CommandBufferArray::CommandBufferArray(
    const VkDevice &logicalDevice,
    const VkCommandBufferAllocateInfo &allocateInfo)
    : Handler("command buffer array", [](const std::vector<VkCommandBuffer> &) {
        Logger::trace(std::cout, "Nothing to be done to destroy command buffer",
                      { "DESTROY" });
    })
{
    Logger::trace(std::cout, "Allocating command buffer array", { "CREATE" });
    getHandle().resize(allocateInfo.commandBufferCount);
    if (vkAllocateCommandBuffers(logicalDevice, &allocateInfo,
                                 getHandle().data())
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not allocate command buffer array",
                         { "CREATE" });
    }
    Logger::trace(std::cout, "Allocated command buffer array", { "CREATE" });
}

const VkCommandBuffer &CommandBufferArray::at(uint32_t index)
{
    return getHandle().at(index);
}

void CommandBufferArray::begin(uint32_t commandBufferIndex, uint32_t imageIndex,
                               const VkRenderPass &renderPass,
                               const SwapchainType &swapchain)
{
    Logger::trace(std::cout,
                  "Beginning command buffer at index "
                      + std::to_string(commandBufferIndex) + " for image "
                      + std::to_string(imageIndex),
                  { "RENDER" });
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;
    beginInfo.pInheritanceInfo = nullptr;

    VkCommandBuffer commandBuffer = at(commandBufferIndex);

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
    {
        Logger::error(std::cout, "Could not begin command buffer",
                      { "RENDER" });
    }
    Logger::trace(std::cout,
                  "Began command buffer at index "
                      + std::to_string(commandBufferIndex) + " for image "
                      + std::to_string(imageIndex),
                  { "RENDER" });

    Logger::trace(std::cout,
                  "Beginning render pass at image index "
                      + std::to_string(imageIndex),
                  { "RENDER" });

    VkRenderPassBeginInfo renderPassBeginInfo{};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.renderPass = renderPass;
    renderPassBeginInfo.framebuffer = swapchain->framebufferAt(imageIndex);
    renderPassBeginInfo.renderArea.offset = { 0, 0 };
    renderPassBeginInfo.renderArea.extent = swapchain->getExtent();

    VkClearValue clearColor = { { CLEAR_COLOR } };
    renderPassBeginInfo.clearValueCount = 1;
    renderPassBeginInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo,
                         VK_SUBPASS_CONTENTS_INLINE);

    Logger::trace(std::cout,
                  "Began render pass at image index "
                      + std::to_string(imageIndex),
                  { "RENDER" });
}

void CommandBufferArray::setViewport(uint32_t commandBufferIndex,
                                     const SwapchainType &swapchain)
{
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = swapchain->getWidth();
    viewport.height = swapchain->getHeight();
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(at(commandBufferIndex), 0, 1, &viewport);
}

void CommandBufferArray::setScissor(uint32_t commandBufferIndex,
                                    const SwapchainType &swapchain)
{
    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = swapchain->getExtent();
    vkCmdSetScissor(at(commandBufferIndex), 0, 1, &scissor);
}

void CommandBufferArray::record(
    uint32_t commandBufferIndex, uint32_t imageIndex,
    const VkRenderPass &renderPass, const SwapchainType &swapchain,
    const GraphicsPipelineType &graphicsPipeline, const VkBuffer &vertexBuffer,
    const VkBuffer &indexBuffer, const std::vector<uint16_t> &indices)
{
    begin(commandBufferIndex, imageIndex, renderPass, swapchain);
    VkCommandBuffer commandBuffer = at(commandBufferIndex);
    graphicsPipeline->bind(commandBuffer);

    setViewport(commandBufferIndex, swapchain);
    setScissor(commandBufferIndex, swapchain);

    VkBuffer vertexBuffers[] = { vertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    uint32_t firstBinding = 0;
    uint32_t bindingCount = 1;
    vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount,
                           vertexBuffers, offsets);
    vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);
    uint32_t instanceCount = 1;
    uint32_t firstVertex = 0;
    uint32_t firstInstance = 0;
    uint32_t instanceOffset = 0;
    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()),
                     instanceCount, firstVertex, firstInstance, instanceOffset);
    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to record command buffer.");
    }
}
