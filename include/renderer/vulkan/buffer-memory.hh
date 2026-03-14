#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

#include <renderer/vulkan/buffer.hh>

namespace brasio::renderer::vulkan
{
    class Buffer;

    class BufferMemory : public core::Handler<VkDeviceMemory>
    {
    public:
        BufferMemory(const PhysicalDeviceType &physicalDevice,
                     const VkDevice &logicalDevice, const Buffer &buffer,
                     VkMemoryPropertyFlags memoryProperties, void *data,
                     size_t size);

    private:
        void *_deviceData;
    };

    using BufferMemoryType = std::unique_ptr<BufferMemory>;
} // namespace brasio::renderer::vulkan
