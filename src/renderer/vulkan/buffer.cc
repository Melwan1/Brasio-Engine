#include <renderer/vulkan/buffer.hh>

#include <cstring>

namespace brasio::renderer::vulkan
{
    Buffer::Buffer(const PhysicalDeviceType &physicalDevice,
                   const LogicalDeviceType &logicalDevice,
                   const VkBufferCreateInfo &createInfo,
                   const VkMemoryPropertyFlags memoryProperties, void *data)
        : Handler("buffer",
                  [&logicalDevice](const VkBuffer &buffer) {
                      vkDestroyBuffer(logicalDevice->getHandle(), buffer,
                                      nullptr);
                  })
        , _logicalDevice(logicalDevice)
        , _deviceMemory(nullptr)
    {
        io::logging::Logger::trace(std::cout, "Creating buffer", { "CREATE" });
        if (vkCreateBuffer(logicalDevice->getHandle(), &createInfo, nullptr,
                           &getHandle())
            != VK_SUCCESS)
        {
            io::logging::Logger::critical(std::cout, "Could not create buffer",
                                          { "CREATE" });
        }
        io::logging::Logger::trace(std::cout, "Created buffer", { "CREATE" });
        _deviceMemory = std::make_unique<BufferMemory>(
            physicalDevice, logicalDevice->getHandle(), *this, memoryProperties,
            data, createInfo.size);
    }

    void Buffer::copyInto(const Buffer &other, VkCommandPool _commandPool,
                          VkDeviceSize size)
    {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = _commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(_logicalDevice->getHandle(), &allocInfo,
                                 &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        VkBufferCopy copyRegion;
        copyRegion.srcOffset = 0;
        copyRegion.dstOffset = 0;
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, getHandle(), other.getHandle(), 1,
                        &copyRegion);
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(_logicalDevice->getGraphicsQueue(), 1, &submitInfo,
                      VK_NULL_HANDLE);
        vkQueueWaitIdle(_logicalDevice->getGraphicsQueue());

        vkFreeCommandBuffers(_logicalDevice->getHandle(), _commandPool, 1,
                             &commandBuffer);
    }
} // namespace brasio::renderer::vulkan
