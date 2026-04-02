#include <renderer/vulkan/command-buffer-array.hh>

#define CLEAR_COLOR                                                            \
    {                                                                          \
        1.0f, 1.0f, 1.0f, 1.0f                                                 \
    }

namespace brasio::renderer::vulkan
{
    CommandBufferArray::CommandBufferArray(
        const VkDevice &logicalDevice,
        const VkCommandBufferAllocateInfo &allocateInfo)
        : Handler(
              "command buffer array", [](const std::vector<VkCommandBuffer> &) {
                  BRASIO_LOG_TRACE(
                      std::cout, "Nothing to be done to destroy command buffer",
                      { "DESTROY" });
              })
    {
        BRASIO_LOG_TRACE(std::cout, "Allocating command buffer array",
                         { "CREATE" });
        getHandle().resize(allocateInfo.commandBufferCount);
        if (vkAllocateCommandBuffers(logicalDevice, &allocateInfo,
                                     getHandle().data())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL(std::cout,
                                "Could not allocate command buffer array",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE(std::cout, "Allocated command buffer array",
                         { "CREATE" });
    }

    const VkCommandBuffer &CommandBufferArray::at(uint32_t index)
    {
        return getHandle().at(index);
    }

    void CommandBufferArray::reset(uint32_t commandBufferIndex)
    {
        vkResetCommandBuffer(at(commandBufferIndex), 0);
    }

    void CommandBufferArray::begin(uint32_t commandBufferIndex,
                                   uint32_t imageIndex,
                                   const VkRenderPass &renderPass,
                                   const Swapchain &swapchain)
    {
        BRASIO_LOG_TRACE(std::cout,
                         "Beginning command buffer at index "
                             + std::to_string(commandBufferIndex)
                             + " for image " + std::to_string(imageIndex),
                         { "RENDER" });
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0;
        beginInfo.pInheritanceInfo = nullptr;

        VkCommandBuffer commandBuffer = at(commandBufferIndex);

        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
        {
            BRASIO_LOG_ERROR(std::cout, "Could not begin command buffer",
                             { "RENDER" });
        }
        BRASIO_LOG_TRACE(std::cout,
                         "Began command buffer at index "
                             + std::to_string(commandBufferIndex)
                             + " for image " + std::to_string(imageIndex),
                         { "RENDER" });

        BRASIO_LOG_TRACE(std::cout,
                         "Beginning render pass at image index "
                             + std::to_string(imageIndex),
                         { "RENDER" });

        VkRenderPassBeginInfo renderPassBeginInfo{};
        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassBeginInfo.renderPass = renderPass;
        renderPassBeginInfo.framebuffer = swapchain.framebufferAt(imageIndex);
        renderPassBeginInfo.renderArea.offset = { 0, 0 };
        renderPassBeginInfo.renderArea.extent = swapchain.getExtent();

        VkClearValue clearColor = { { CLEAR_COLOR } };
        renderPassBeginInfo.clearValueCount = 1;
        renderPassBeginInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo,
                             VK_SUBPASS_CONTENTS_INLINE);

        BRASIO_LOG_TRACE(std::cout,
                         "Began render pass at image index "
                             + std::to_string(imageIndex),
                         { "RENDER" });
    }

    void CommandBufferArray::setViewport(uint32_t commandBufferIndex,
                                         const Swapchain &swapchain)
    {
        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = swapchain.getWidth();
        viewport.height = swapchain.getHeight();
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(at(commandBufferIndex), 0, 1, &viewport);
    }

    void CommandBufferArray::setScissor(uint32_t commandBufferIndex,
                                        const Swapchain &swapchain)
    {
        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = swapchain.getExtent();
        vkCmdSetScissor(at(commandBufferIndex), 0, 1, &scissor);
    }

    void CommandBufferArray::record(const VulkanRenderer &renderer,
                                    uint32_t commandBufferIndex,
                                    uint32_t imageIndex)
    {
        begin(commandBufferIndex, imageIndex,
              renderer.getRenderPass().getHandle(), renderer.getSwapchain());
        VkCommandBuffer commandBuffer = at(commandBufferIndex);

        setViewport(commandBufferIndex, renderer.getSwapchain());
        setScissor(commandBufferIndex, renderer.getSwapchain());

        for (const GraphicsPipelineType &graphicsPipeline :
             renderer.getGraphicsPipelines())
        {
            graphicsPipeline->bind(commandBuffer);
            renderer.getMesh1().draw(commandBuffer, renderer);
            renderer.getMesh2().draw(commandBuffer, renderer);
        }

        vkCmdEndRenderPass(commandBuffer);

        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL(std::cout,
                                "Failed to end command buffer recording");
        }
    }
} // namespace brasio::renderer::vulkan
