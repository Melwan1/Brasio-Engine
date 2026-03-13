#include <renderer/vulkan/buffer-memory.hh>

#include <cstring>

BufferMemory::BufferMemory(const PhysicalDeviceType &physicalDevice,
                           const VkDevice &logicalDevice, const Buffer &buffer,
                           VkMemoryPropertyFlags memoryProperties, void *data,
                           size_t size)
    : Handler("buffer memory",
              [logicalDevice](const VkDeviceMemory &bufferMemory) {
                  vkFreeMemory(logicalDevice, bufferMemory, nullptr);
              })
{
    Logger::trace(std::cout, "Binding buffer memory", { "CREATE" });
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(logicalDevice, buffer.getHandle(),
                                  &memoryRequirements);

    VkMemoryAllocateInfo memoryAllocateInfo{};
    memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memoryAllocateInfo.allocationSize = memoryRequirements.size;
    memoryAllocateInfo.memoryTypeIndex = physicalDevice->findMemoryType(
        memoryRequirements.memoryTypeBits, memoryProperties);

    if (vkAllocateMemory(logicalDevice, &memoryAllocateInfo, nullptr,
                         &getHandle())
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not bind buffer memory",
                         { "CREATE" });
    }
    vkBindBufferMemory(logicalDevice, buffer.getHandle(), getHandle(), 0);
    Logger::trace(std::cout, "Bound buffer memory", { "CREATE" });

    if (data != nullptr)
    {
        Logger::trace(std::cout, "Transferring buffer memory to device",
                      { "CREATE" });
        vkMapMemory(logicalDevice, getHandle(), 0, size, 0, &_deviceData);
        std::memcpy(_deviceData, data, size);
        vkUnmapMemory(logicalDevice, getHandle());
        Logger::trace(std::cout, "Transferred buffer memory to device",
                      { "CREATE" });
    }
}
