#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

#include <renderer/vulkan/physical-device.hh>
#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/buffer-memory.hh>

class BufferMemory;
using BufferMemoryType = std::unique_ptr<BufferMemory>;

class Buffer : public Handler<VkBuffer>
{
public:
    Buffer(const PhysicalDeviceType &physicalDevice,
           const LogicalDeviceType &logicalDevice,
           const VkBufferCreateInfo &createInfo,
           const VkMemoryPropertyFlags memoryProperties, void *data);

    void copyInto(const Buffer &other, VkCommandPool _commandPool,
                  VkDeviceSize size);

private:
    const LogicalDeviceType &_logicalDevice;
    BufferMemoryType _deviceMemory;
    void *_deviceData;
};

using BufferType = std::unique_ptr<Buffer>;
