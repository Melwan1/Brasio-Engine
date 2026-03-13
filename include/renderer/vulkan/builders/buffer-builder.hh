#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/buffer.hh>

class BufferBuilder : public Builder<BufferType>
{
public:
    BufferBuilder(const PhysicalDeviceType &physicalDevice,
                  const LogicalDeviceType &logicalDevice);

    virtual BufferBuilder &base() override;
    virtual BufferType build() override;

    BufferBuilder &withSize(uint32_t size);
    BufferBuilder &withUsage(const VkBufferUsageFlags &usage);
    BufferBuilder &withSharingMode(const VkSharingMode &sharingMode);
    BufferBuilder &
    withMemoryProperties(const VkMemoryPropertyFlags &memoryProperties);

    BufferBuilder &withData(void *data);

private:
    const PhysicalDeviceType &_physicalDevice;
    const LogicalDeviceType &_logicalDevice;
    VkStructureType _structureType;

    uint32_t _size;
    VkBufferUsageFlags _usage;
    VkSharingMode _sharingMode;
    VkMemoryPropertyFlags _memoryProperties;

    void *_data;
};
