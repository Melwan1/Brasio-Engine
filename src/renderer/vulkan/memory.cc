#include <renderer/vulkan/memory.hh>

#include <renderer/vulkan/buffer.hh>
#include <renderer/vulkan/image-attachment.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

#include <cstring>

namespace brasio::renderer::vulkan
{
    Memory::Memory(const VulkanRenderer &renderer, const Buffer &buffer,
                   VkMemoryPropertyFlags memoryProperties, void *data, size_t size)
        : Handler("memory",
                  [&renderer](const VkDeviceMemory &bufferMemory) {
                      vkFreeMemory(renderer.getLogicalDevice(), bufferMemory, nullptr);
                  })
        , _renderer(renderer)
        , _size(size)
    {
        BRASIO_LOG_TRACE("Creating memory memory", { "CREATE" });
        VkMemoryRequirements memoryRequirements;
        vkGetBufferMemoryRequirements(renderer.getLogicalDevice(), buffer.getHandle(),
                                      &memoryRequirements);

        allocate(memoryProperties, memoryRequirements);

        vkBindBufferMemory(renderer.getLogicalDevice(), buffer.getHandle(), getHandle(), 0);
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

    Memory::Memory(const VulkanRenderer &renderer, const ImageAttachment &imageAttachment,
                   VkMemoryPropertyFlags memoryProperties)
        : Handler("memory",
                  [&renderer](const VkDeviceMemory &bufferMemory) {
                      vkFreeMemory(renderer.getLogicalDevice(), bufferMemory, nullptr);
                  })
        , _renderer(renderer)
        , _size(imageAttachment.getSize())
    {
        BRASIO_LOG_TRACE("Creating texture memory", { "CREATE" });
        VkMemoryRequirements memoryRequirements;
        vkGetImageMemoryRequirements(renderer.getLogicalDevice(), imageAttachment.getImage(),
                                     &memoryRequirements);

        allocate(memoryProperties, memoryRequirements);

        vkBindImageMemory(renderer.getLogicalDevice(), imageAttachment.getImage(), getHandle(), 0);
        BRASIO_LOG_TRACE("Bound texture memory", { "CREATE" });
    }

    void Memory::allocate(const VkMemoryPropertyFlags &memoryProperties,
                          const VkMemoryRequirements &memoryRequirements)
    {
        VkMemoryAllocateInfo memoryAllocateInfo{};
        memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memoryAllocateInfo.allocationSize = memoryRequirements.size;
        memoryAllocateInfo.memoryTypeIndex = _renderer.getPhysicalDeviceWrapper().findMemoryType(
            memoryRequirements.memoryTypeBits, memoryProperties);

        BRASIO_VULKAN_CHECK(vkAllocateMemory(_renderer.getLogicalDevice(), &memoryAllocateInfo,
                                             nullptr, &getHandle()),
                            "allocate memory", { "CREATE" });
    }

    void Memory::map()
    {
        vkMapMemory(_renderer.getLogicalDevice(), getHandle(), 0, _size, 0, &_deviceData);
    }

    void Memory::unmap()
    {
        vkUnmapMemory(_renderer.getLogicalDevice(), getHandle());
    }

    void Memory::setContent(const void *content)
    {
        std::memcpy(_deviceData, content, _size);
    }
} // namespace brasio::renderer::vulkan
