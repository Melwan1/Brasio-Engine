#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

#include <renderer/vulkan/swapchain.hh>
#include <renderer/vulkan/graphics-pipeline.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::renderer::vulkan
{

    class VulkanRenderer;
}

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
                   const VkRenderPass &renderPass, const Swapchain &swapchain);

        void setViewport(uint32_t commandBufferIndex,
                         const Swapchain &swapchain);

        void setScissor(uint32_t commandBufferIndex,
                        const Swapchain &swapchain);

        void record(const VulkanRenderer &renderer, uint32_t commandBufferIndex,
                    uint32_t imageIndex);
    };

    using CommandBufferArrayType = std::unique_ptr<CommandBufferArray>;
} // namespace brasio::renderer::vulkan
