#pragma once

#include <core/builder.hh>

#include <renderer/vulkan/command-buffer-array.hh>
#include <renderer/vulkan/swapchain.hh>

namespace brasio::renderer::vulkan::builders
{
    class CommandBufferArrayBuilder
        : public core::Builder<CommandBufferArrayType>
    {
    public:
        CommandBufferArrayBuilder(const VkDevice &logicalDevice,
                                  const VkCommandPool &commandPool);

        virtual CommandBufferArrayBuilder &base() override;
        virtual CommandBufferArrayType build() override;

        CommandBufferArrayBuilder &withLevel(const VkCommandBufferLevel &level);
        CommandBufferArrayBuilder &
        withCommandBufferCount(uint32_t commandBufferCount);

    private:
        VkDevice _logicalDevice;
        VkCommandPool _commandPool;

        VkStructureType _structureType;
        VkCommandBufferLevel _level;
        uint32_t _commandBufferCount;
    };
} // namespace brasio::renderer::vulkan::builders
