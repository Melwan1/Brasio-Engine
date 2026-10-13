#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

#include <renderer/renderable.hh>
#include <renderer/vulkan/swapchain.hh>
#include <renderer/vulkan/graphics-pipeline.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class CommandBufferArray : public core::Handler<std::vector<VkCommandBuffer>>
    {
    public:
        CommandBufferArray(const VulkanRenderer &renderer,
                           const VkCommandBufferAllocateInfo &allocateInfo);

        const VkCommandBuffer &at(uint32_t index);

        void reset(uint32_t commandBufferIndex);

        void begin(uint32_t commandBufferIndex, uint32_t imageIndex);

        void record(uint32_t commandBufferIndex, uint32_t imageIndex, Renderable &root);

        void recordCompute(uint32_t commandBufferIndex, uint32_t workGroupCount);

    private:
        const VulkanRenderer &_renderer;
    };

    using CommandBufferArrayType = std::unique_ptr<CommandBufferArray>;
} // namespace brasio::renderer::vulkan
