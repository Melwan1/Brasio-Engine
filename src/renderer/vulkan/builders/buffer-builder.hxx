#pragma once

#include <renderer/vulkan/builders/buffer-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    template <VkBufferUsageFlags usage, VkMemoryPropertyFlags memoryProperties>
    BufferBuilder<usage, memoryProperties>::BufferBuilder(const PhysicalDeviceType &physicalDevice,
                                                          const LogicalDeviceType &logicalDevice)
        : _physicalDevice(physicalDevice)
        , _logicalDevice(logicalDevice)
    {
        base();
    }

    template <VkBufferUsageFlags usage, VkMemoryPropertyFlags memoryProperties>
    BufferBuilder<usage, memoryProperties> &BufferBuilder<usage, memoryProperties>::base()
    {
        _structureType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        return withSize(0).withSharingMode(VK_SHARING_MODE_EXCLUSIVE).withData(nullptr);
    }

    template <VkBufferUsageFlags usage, VkMemoryPropertyFlags memoryProperties>
    BufferBuilder<usage, memoryProperties> &
    BufferBuilder<usage, memoryProperties>::withSize(uint32_t size)
    {
        _size = size;
        return *this;
    }

    template <VkBufferUsageFlags usage, VkMemoryPropertyFlags memoryProperties>
    BufferBuilder<usage, memoryProperties> &
    BufferBuilder<usage, memoryProperties>::withSharingMode(const VkSharingMode &sharingMode)
    {
        _sharingMode = sharingMode;
        return *this;
    }

    template <VkBufferUsageFlags usage, VkMemoryPropertyFlags memoryProperties>
    BufferBuilder<usage, memoryProperties> &
    BufferBuilder<usage, memoryProperties>::withData(void *data)
    {
        _data = data;
        return *this;
    }

    template <VkBufferUsageFlags usage, VkMemoryPropertyFlags memoryProperties>
    BufferType BufferBuilder<usage, memoryProperties>::build()
    {
        if (_size == 0)
        {
            BRASIO_LOG_WARNING("Buffer has size == 0", { "BUFFER" });
        }
        VkBufferCreateInfo bufferCreateInfo{};
        bufferCreateInfo.sType = _structureType;
        bufferCreateInfo.size = _size;
        bufferCreateInfo.usage = usage;
        bufferCreateInfo.sharingMode = _sharingMode;

        return std::make_unique<Buffer>(_physicalDevice, _logicalDevice, bufferCreateInfo,
                                        memoryProperties, _data, _size);
    }
} // namespace brasio::renderer::vulkan::builders
