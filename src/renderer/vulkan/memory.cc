#include <renderer/vulkan/memory.hh>

#include <renderer/vulkan/buffer.hh>
#include <renderer/vulkan/image-attachment.hh>
#include <utils/libutils.hh>

#include <cstring>

namespace brasio::renderer::vulkan
{
    Memory::Memory(const PhysicalDeviceType &physicalDevice,
                   const VkDevice &logicalDevice, const Buffer &buffer,
                   VkMemoryPropertyFlags memoryProperties, void *data,
                   size_t size)
        : Handler("memory",
                  [logicalDevice](const VkDeviceMemory &bufferMemory) {
                      vkFreeMemory(logicalDevice, bufferMemory, nullptr);
                  })
        , _logicalDevice(logicalDevice)
        , _size(size)
    {
        BRASIO_LOG_TRACE("Creating memory memory", { "CREATE" });
        VkMemoryRequirements memoryRequirements;
        vkGetBufferMemoryRequirements(logicalDevice, buffer.getHandle(),
                                      &memoryRequirements);

        allocate(physicalDevice, logicalDevice, memoryProperties,
                 memoryRequirements);

        vkBindBufferMemory(logicalDevice, buffer.getHandle(), getHandle(), 0);
        BRASIO_LOG_TRACE("Bound buffer memory", { "CREATE" });

        if (data == nullptr)
        {
            return;
        }
        BRASIO_LOG_TRACE("Transferring buffer memory to device", { "CREATE" });
        map();
        setContent(data);
        unmap();
        BRASIO_LOG_TRACE("Transferred buffer memory to device", { "CREATE" });
    }

    Memory::Memory(const PhysicalDeviceType &physicalDevice,
                   const VkDevice &logicalDevice,
                   const ImageAttachment &imageAttachment,
                   VkMemoryPropertyFlags memoryProperties)
        : Handler("memory",
                  [logicalDevice](const VkDeviceMemory &bufferMemory) {
                      vkFreeMemory(logicalDevice, bufferMemory, nullptr);
                  })
        , _logicalDevice(logicalDevice)
        , _size(imageAttachment.getSize())
    {
        BRASIO_LOG_TRACE("Creating texture memory", { "CREATE" });
        VkMemoryRequirements memoryRequirements;
        vkGetImageMemoryRequirements(logicalDevice, imageAttachment.getImage(),
                                     &memoryRequirements);

        allocate(physicalDevice, logicalDevice, memoryProperties,
                 memoryRequirements);

        vkBindImageMemory(logicalDevice, imageAttachment.getImage(),
                          getHandle(), 0);
        BRASIO_LOG_TRACE("Bound texture memory", { "CREATE" });
    }

    void Memory::allocate(const PhysicalDeviceType &physicalDevice,
                          const VkDevice &logicalDevice,
                          const VkMemoryPropertyFlags &memoryProperties,
                          const VkMemoryRequirements &memoryRequirements)
    {
        VkMemoryAllocateInfo memoryAllocateInfo{};
        memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memoryAllocateInfo.allocationSize = memoryRequirements.size;
        memoryAllocateInfo.memoryTypeIndex = physicalDevice->findMemoryType(
            memoryRequirements.memoryTypeBits, memoryProperties);

        BRASIO_VULKAN_CHECK(vkAllocateMemory(logicalDevice, &memoryAllocateInfo,
                                             nullptr, &getHandle()),
                            "allocate memory", { "CREATE" });
    }

    void Memory::map()
    {
        vkMapMemory(_logicalDevice, getHandle(), 0, _size, 0, &_deviceData);
    }

    void Memory::unmap()
    {
        vkUnmapMemory(_logicalDevice, getHandle());
    }

    void Memory::setContent(const void *content)
    {
        std::memcpy(_deviceData, content, _size);
    }
} // namespace brasio::renderer::vulkan
