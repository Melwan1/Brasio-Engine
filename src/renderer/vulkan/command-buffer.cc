#include <renderer/vulkan/command-buffer.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::renderer::vulkan
{

    CommandBuffer::CommandBuffer(const VulkanRenderer &renderer)
        : Handler("command buffer",
                  [this, &renderer](const VkCommandBuffer &commandBuffer) {
                      if (!_ended)
                      {
                          end();
                      }
                      vkFreeCommandBuffers(renderer.getLogicalDevice(), renderer.getCommandPool(),
                                           1, &commandBuffer);
                  })
        , _ended(false)
        , _renderer(renderer)
    {
        begin();
    }

    void CommandBuffer::begin()
    {
        VkCommandBufferAllocateInfo allocateInfo{};
        allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocateInfo.commandPool = _renderer.getCommandPool();
        allocateInfo.commandBufferCount = 1;

        vkAllocateCommandBuffers(_renderer.getLogicalDevice(), &allocateInfo, &getHandle());

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

        vkQueueSubmit(_renderer.getLogicalDeviceWrapper().getGraphicsQueue(), 1, &submitInfo,
                      VK_NULL_HANDLE);
        vkQueueWaitIdle(_renderer.getLogicalDeviceWrapper().getGraphicsQueue());
        _ended = true;
    }
} // namespace brasio::renderer::vulkan
