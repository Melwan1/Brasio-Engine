#include <renderer/vulkan/builders/buffer-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    BufferBuilder::BufferBuilder(const PhysicalDeviceType &physicalDevice,
                                 const LogicalDeviceType &logicalDevice)
        : _physicalDevice(physicalDevice)
        , _logicalDevice(logicalDevice)
    {
        base();
    }

    BufferBuilder &BufferBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        return withSize(0)
            .withUsage(VK_BUFFER_USAGE_FLAG_BITS_MAX_ENUM)
            .withSharingMode(VK_SHARING_MODE_EXCLUSIVE)
            .withData(nullptr);
    }

    BufferBuilder &BufferBuilder::withSize(uint32_t size)
    {
        _size = size;
        return *this;
    }

    BufferBuilder &BufferBuilder::withUsage(const VkBufferUsageFlags &usage)
    {
        _usage = usage;
        return *this;
    }

    BufferBuilder &BufferBuilder::withMemoryProperties(
        const VkMemoryPropertyFlags &memoryProperties)
    {
        _memoryProperties = memoryProperties;
        return *this;
    }

    BufferBuilder &
    BufferBuilder::withSharingMode(const VkSharingMode &sharingMode)
    {
        _sharingMode = sharingMode;
        return *this;
    }

    BufferBuilder &BufferBuilder::withData(void *data)
    {
        _data = data;
        return *this;
    }

    BufferType BufferBuilder::build()
    {
        VkBufferCreateInfo bufferCreateInfo{};
        bufferCreateInfo.sType = _structureType;
        bufferCreateInfo.size = _size;
        bufferCreateInfo.usage = _usage;
        bufferCreateInfo.sharingMode = _sharingMode;

        return std::make_unique<Buffer>(_physicalDevice, _logicalDevice,
                                        bufferCreateInfo, _memoryProperties,
                                        _data);
    }
} // namespace brasio::renderer::vulkan::builders
