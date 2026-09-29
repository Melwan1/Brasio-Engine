#pragma once

#include <renderer/vulkan/builders/buffer-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    class StagingBufferBuilder : public BufferBuilder
    {
    public:
        StagingBufferBuilder(const PhysicalDeviceType &physicalDevice,
                             const LogicalDeviceType &logicalDevice);

        StagingBufferBuilder &base() override;
    };
} // namespace brasio::renderer::vulkan::builders
