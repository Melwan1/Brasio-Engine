#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

#include <renderer/vulkan/physical-device.hh>
#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/memory.hh>

namespace brasio::renderer::vulkan
{
    class Memory;
    using MemoryType = std::unique_ptr<Memory>;

    class Buffer : public core::Handler<VkBuffer>
    {
    public:
        Buffer(const PhysicalDeviceType &physicalDevice,
               const LogicalDeviceType &logicalDevice,
               const VkBufferCreateInfo &createInfo,
               const VkMemoryPropertyFlags memoryProperties, void *data);

        void copyInto(const Buffer &other, VkCommandPool _commandPool,
                      VkDeviceSize size);

        void mapMemory();
        void unmapMemory();
        void setContent(void *content);

    private:
        const LogicalDeviceType &_logicalDevice;
        MemoryType _deviceMemory;
        void *_deviceData;
    };

    using BufferType = std::unique_ptr<Buffer>;
} // namespace brasio::renderer::vulkan
