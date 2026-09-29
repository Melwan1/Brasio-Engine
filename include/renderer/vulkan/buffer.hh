#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

#include <renderer/vulkan/physical-device.hh>
#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/memory.hh>
#include <renderer/vulkan/image-attachment.hh>

namespace brasio::renderer::vulkan
{
    class Memory;
    using MemoryType = std::unique_ptr<Memory>;

    class Buffer : public core::Handler<VkBuffer>
    {
    public:
        Buffer(const PhysicalDeviceType &physicalDevice, const LogicalDeviceType &logicalDevice,
               const VkBufferCreateInfo &createInfo, const VkMemoryPropertyFlags memoryProperties,
               void *data, VkDeviceSize size);

        void copyInto(const Buffer &other, VkCommandPool commandPool);
        void copyInto(const ImageAttachment &other, VkCommandPool commandPool);

        void mapMemory();
        void unmapMemory();
        void setContent(void *content);

        VkDeviceSize getSize() const;

    private:
        const LogicalDeviceType &_logicalDevice;
        MemoryType _deviceMemory;
        void *_deviceData;
        VkDeviceSize _size;
    };

    using BufferType = std::unique_ptr<Buffer>;
} // namespace brasio::renderer::vulkan
