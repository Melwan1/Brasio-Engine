#include <renderer/vulkan/command-buffer-array.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    CommandBufferArray::CommandBufferArray(
        const VkDevice &logicalDevice,
        const VkCommandBufferAllocateInfo &allocateInfo)
        : Handler("command buffer array",
                  [](const std::vector<VkCommandBuffer> &) {
                      BRASIO_LOG_TRACE(
                          "Nothing to be done to destroy command buffer",
                          { "DESTROY" });
                  })
    {
        BRASIO_LOG_TRACE("Allocating command buffer array", { "CREATE" });
        getHandle().resize(allocateInfo.commandBufferCount);
        BRASIO_VULKAN_CHECK(vkAllocateCommandBuffers(logicalDevice,
                                                     &allocateInfo,
                                                     getHandle().data()),
                            "allocate command buffer array", { "CREATE" });
        BRASIO_LOG_TRACE("Allocated command buffer array", { "CREATE" });
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
        BRASIO_LOG_TRACE("Beginning command buffer at index "
                             + std::to_string(commandBufferIndex)
                             + " for image " + std::to_string(imageIndex),
                         { "RENDER" });
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0;
        beginInfo.pInheritanceInfo = nullptr;

        VkCommandBuffer commandBuffer = at(commandBufferIndex);

        BRASIO_VULKAN_CHECK(vkBeginCommandBuffer(commandBuffer, &beginInfo),
                            "begin command buffer", { "RENDER" });
        BRASIO_LOG_TRACE("Began command buffer at index "
                             + std::to_string(commandBufferIndex)
                             + " for image " + std::to_string(imageIndex),
                         { "RENDER" });

        BRASIO_LOG_TRACE("Beginning render pass at image index "
                             + std::to_string(imageIndex),
                         { "RENDER" });

        VkRenderPassBeginInfo renderPassBeginInfo{};
        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassBeginInfo.renderPass = renderPass;
        renderPassBeginInfo.framebuffer = swapchain.framebufferAt(imageIndex);
        renderPassBeginInfo.renderArea.offset = { 0, 0 };
        renderPassBeginInfo.renderArea.extent = swapchain.getExtent();

        std::array<VkClearValue, 3> clearValues{};
        clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 0.0f } };
        clearValues[1].depthStencil = { 1.0f, 0 };
        clearValues[2].color = { { 0.0f, 0.0f, 0.0f, 0.0f } };
        renderPassBeginInfo.clearValueCount = clearValues.size();
        renderPassBeginInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo,
                             VK_SUBPASS_CONTENTS_INLINE);

        BRASIO_LOG_TRACE("Began render pass at image index "
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
        BRASIO_LOG_TRACE("Starting command buffer record", { "RENDER" });
        begin(commandBufferIndex, imageIndex,
              renderer.getRenderPass().getHandle(), renderer.getSwapchain());
        VkCommandBuffer commandBuffer = at(commandBufferIndex);

        BRASIO_LOG_TRACE("Setting viewport and scissor", { "RENDER" });
        setViewport(commandBufferIndex, renderer.getSwapchain());
        setScissor(commandBufferIndex, renderer.getSwapchain());

        for (const GraphicsPipelineType &graphicsPipeline :
             renderer.getGraphicsPipelines())
        {
            BRASIO_LOG_TRACE("Binding graphics pipeline", { "RENDER" });
            graphicsPipeline->bind(commandBuffer);
            BRASIO_LOG_TRACE("Rendering mesh 1", { "RENDER" });
            renderer.getMesh1().draw(commandBuffer, renderer);
            BRASIO_LOG_TRACE("Rendering mesh 2", { "RENDER" });
            // renderer.getMesh2().draw(commandBuffer, renderer);
        }

        BRASIO_LOG_TRACE("Ending render pass", { "RENDER" });
        vkCmdEndRenderPass(commandBuffer);

        BRASIO_LOG_TRACE("Ending command buffer", { "RENDER" });

        BRASIO_VULKAN_CHECK(vkEndCommandBuffer(commandBuffer),
                            "end command buffer record", { "RENDER" });
    }
} // namespace brasio::renderer::vulkan
