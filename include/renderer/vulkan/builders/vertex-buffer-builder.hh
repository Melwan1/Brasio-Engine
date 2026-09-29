#pragma once

#include <renderer/vulkan/builders/buffer-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    class VertexBufferBuilder : public BufferBuilder
    {
    public:
        VertexBufferBuilder(const PhysicalDeviceType &physicalDevice,
                            const LogicalDeviceType &logicalDevice);

        VertexBufferBuilder &base() override;
    };
} // namespace brasio::renderer::vulkan::builders
