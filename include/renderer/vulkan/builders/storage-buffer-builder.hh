#pragma once

#include <renderer/vulkan/builders/buffer-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    class StorageBufferBuilder : public BufferBuilder
    {
    public:
        StorageBufferBuilder(const PhysicalDeviceType &physicalDevice,
                             const LogicalDeviceType &logicalDevice);

        StorageBufferBuilder &base() override;
    };

} // namespace brasio::renderer::vulkan::builders
