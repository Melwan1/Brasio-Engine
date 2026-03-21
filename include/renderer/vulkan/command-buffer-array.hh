#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

#include <renderer/vulkan/swapchain.hh>
#include <renderer/vulkan/graphics-pipeline.hh>

namespace brasio::renderer::vulkan
{
    class CommandBufferArray
        : public core::Handler<std::vector<VkCommandBuffer>>
    {
    public:
        CommandBufferArray(const VkDevice &logicalDevice,
                           const VkCommandBufferAllocateInfo &allocateInfo);

        const VkCommandBuffer &at(uint32_t index);

        void reset(uint32_t commandBufferIndex);

        void begin(uint32_t commandBufferIndex, uint32_t imageIndex,
                   const VkRenderPass &renderPass,
                   const SwapchainType &swapchain);

        void setViewport(uint32_t commandBufferIndex,
                         const SwapchainType &swapchain);

        void setScissor(uint32_t commandBufferIndex,
                        const SwapchainType &swapchain);

        void record(uint32_t commandBufferIndex, uint32_t imageIndex,
                    const VkRenderPass &renderPass,
                    const SwapchainType &swapchain,
                    const GraphicsPipelineType &graphicsPipeline,
                    const VkPipelineLayout &layout,
                    const VkDescriptorSet &descriptorSet,
                    const VkBuffer &vertexBuffer, const VkBuffer &indexBuffer,
                    const std::vector<uint16_t> &indices);
    };

    using CommandBufferArrayType = std::unique_ptr<CommandBufferArray>;
} // namespace brasio::renderer::vulkan
