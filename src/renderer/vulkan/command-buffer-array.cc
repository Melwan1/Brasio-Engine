#include <renderer/vulkan/command-buffer-array.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    CommandBufferArray::CommandBufferArray(const VulkanRenderer &renderer,
                                           const VkCommandBufferAllocateInfo &allocateInfo)
        : Handler("command buffer array",
                  [](const std::vector<VkCommandBuffer> &) {
                      BRASIO_LOG_TRACE("Nothing to be done to destroy command buffer",
                                       { "DESTROY" });
                  })
        , _renderer(renderer)
    {
        BRASIO_LOG_TRACE("Allocating command buffer array", { "CREATE" });
        getHandle().resize(allocateInfo.commandBufferCount);
        BRASIO_VULKAN_CHECK(vkAllocateCommandBuffers(renderer.getLogicalDevice(), &allocateInfo,
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

    void CommandBufferArray::begin(uint32_t commandBufferIndex, uint32_t imageIndex)
    {
        BRASIO_LOG_TRACE("Beginning command buffer at index " + std::to_string(commandBufferIndex)
                             + " for image " + std::to_string(imageIndex),
                         { "RENDER" });
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0;
        beginInfo.pInheritanceInfo = nullptr;

        VkCommandBuffer commandBuffer = at(commandBufferIndex);

        BRASIO_VULKAN_CHECK(vkBeginCommandBuffer(commandBuffer, &beginInfo), "begin command buffer",
                            { "RENDER" });
        BRASIO_LOG_TRACE("Began command buffer at index " + std::to_string(commandBufferIndex)
                             + " for image " + std::to_string(imageIndex),
                         { "RENDER" });

        BRASIO_LOG_TRACE("Beginning render pass at image index " + std::to_string(imageIndex),
                         { "RENDER" });

        VkRenderPassBeginInfo renderPassBeginInfo{};
        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassBeginInfo.renderPass = _renderer.getRenderPass();
        renderPassBeginInfo.framebuffer = _renderer.getSwapchain().framebufferAt(imageIndex);
        renderPassBeginInfo.renderArea.offset = { 0, 0 };
        renderPassBeginInfo.renderArea.extent = _renderer.getSwapchain().getExtent();

        std::array<VkClearValue, 3> clearValues{};
        clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 0.0f } };
        clearValues[1].depthStencil = { 1.0f, 0 };
        clearValues[2].color = { { 0.0f, 0.0f, 0.0f, 0.0f } };
        renderPassBeginInfo.clearValueCount = clearValues.size();
        renderPassBeginInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        BRASIO_LOG_TRACE("Began render pass at image index " + std::to_string(imageIndex),
                         { "RENDER" });
    }

    void CommandBufferArray::setViewport(uint32_t commandBufferIndex)
    {
        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = _renderer.getSwapchain().getWidth();
        viewport.height = _renderer.getSwapchain().getHeight();
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(at(commandBufferIndex), 0, 1, &viewport);
    }

    void CommandBufferArray::setScissor(uint32_t commandBufferIndex)
    {
        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = _renderer.getSwapchain().getExtent();
        vkCmdSetScissor(at(commandBufferIndex), 0, 1, &scissor);
    }

    void CommandBufferArray::record(uint32_t commandBufferIndex, uint32_t imageIndex)
    {
        BRASIO_LOG_TRACE("Starting command buffer record", { "RENDER" });
        begin(commandBufferIndex, imageIndex);
        VkCommandBuffer commandBuffer = at(commandBufferIndex);

        BRASIO_LOG_TRACE("Setting viewport and scissor", { "RENDER" });
        setViewport(commandBufferIndex);
        setScissor(commandBufferIndex);

        for (const GraphicsPipelineType &graphicsPipeline : _renderer.getGraphicsPipelines())
        {
            BRASIO_LOG_TRACE("Binding graphics pipeline", { "RENDER" });
            graphicsPipeline->bind(commandBuffer);
            BRASIO_LOG_TRACE("Rendering particles", { "RENDER" });
            VkBuffer vertexBuffers[] = { _renderer.getParticleVertexBuffer() };
            VkDeviceSize offsets[] = { 0 };
            vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
            vkCmdDraw(commandBuffer, _renderer.getParticleCount(), 1, 0, 0);
        }

        BRASIO_LOG_TRACE("Ending render pass", { "RENDER" });
        vkCmdEndRenderPass(commandBuffer);

        BRASIO_LOG_TRACE("Ending command buffer", { "RENDER" });

        BRASIO_VULKAN_CHECK(vkEndCommandBuffer(commandBuffer), "end command buffer record",
                            { "RENDER" });
    }

    void CommandBufferArray::recordCompute(uint32_t commandBufferIndex, uint32_t workGroupCount)
    {
        BRASIO_LOG_TRACE("Starting compute command buffer record", { "COMPUTE" });

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0;
        beginInfo.pInheritanceInfo = nullptr;

        VkCommandBuffer commandBuffer = at(commandBufferIndex);
        BRASIO_VULKAN_CHECK(vkBeginCommandBuffer(commandBuffer, &beginInfo),
                            "begin compute command buffer", { "COMPUTE" });

        for (const ComputePipelineType &computePipeline : _renderer.getComputePipelines())
        {
            BRASIO_LOG_TRACE("Binding compute pipeline", { "COMPUTE" });
            computePipeline->bind(commandBuffer);
            vkCmdBindDescriptorSets(
                commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
                computePipeline->getPipelineLayout().getHandle(), 0, 1,
                &_renderer.getComputeDescriptorSets().getHandle().at(_renderer.getCurrentFrame()),
                0, nullptr);
            BRASIO_LOG_TRACE("Dispatching compute", { "COMPUTE" });
            vkCmdDispatch(commandBuffer, workGroupCount, 1, 1);
        }

        BRASIO_VULKAN_CHECK(vkEndCommandBuffer(commandBuffer), "end compute command buffer record",
                            { "COMPUTE" });
    }
} // namespace brasio::renderer::vulkan
