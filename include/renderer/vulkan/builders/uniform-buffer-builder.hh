#pragma once

#include <renderer/vulkan/builders/buffer-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    class UniformBufferBuilder : public BufferBuilder
    {
    public:
        UniformBufferBuilder(const PhysicalDeviceType &physicalDevice,
                             const LogicalDeviceType &logicalDevice);

        UniformBufferBuilder &base() override;
    };
} // namespace brasio::renderer::vulkan::builders
