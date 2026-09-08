#include <renderer/vulkan/command-buffer.hh>

namespace brasio::renderer::vulkan
{

    CommandBuffer::CommandBuffer(const LogicalDeviceType &logicalDevice,
                                 const VkCommandPool &commandPool)
        : Handler("command buffer",
                  [this, &logicalDevice,
                   commandPool](const VkCommandBuffer &commandBuffer) {
                      if (!_ended)
                      {
                          end();
                      }
                      vkFreeCommandBuffers(logicalDevice->getHandle(),
                                           commandPool, 1, &commandBuffer);
                  })
        , _logicalDevice(logicalDevice)
        , _commandPool(commandPool)
    {
        begin();
    }

    void CommandBuffer::begin()
    {
        VkCommandBufferAllocateInfo allocateInfo{};
        allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocateInfo.commandPool = _commandPool;
        allocateInfo.commandBufferCount = 1;

        vkAllocateCommandBuffers(_logicalDevice->getHandle(), &allocateInfo,
                                 &getHandle());

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(getHandle(), &beginInfo);
    }

    void CommandBuffer::end()
    {
        vkEndCommandBuffer(getHandle());
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &getHandle();

        vkQueueSubmit(_logicalDevice->getGraphicsQueue(), 1, &submitInfo,
                      VK_NULL_HANDLE);
        vkQueueWaitIdle(_logicalDevice->getGraphicsQueue());
        _ended = true;
    }
} // namespace brasio::renderer::vulkan
