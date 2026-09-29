#pragma once

#include <renderer/vulkan/builders/buffer-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    class IndexBufferBuilder : public BufferBuilder
    {
    public:
        IndexBufferBuilder(const PhysicalDeviceType &physicalDevice,
                           const LogicalDeviceType &logicalDevice);

        IndexBufferBuilder &base() override;
    };
} // namespace brasio::renderer::vulkan::builders
