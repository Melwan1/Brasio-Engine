#include <renderer/vulkan/command-buffer-array.hh>

CommandBufferArray::CommandBufferArray(
    const VkDevice &logicalDevice,
    const VkCommandBufferAllocateInfo &allocateInfo)
    : Handler("command buffer array", [](const std::vector<VkCommandBuffer> &) {
        Logger::trace(std::cout, "Nothing to be done to destroy command buffer",
                      { "DESTROY" });
    })
{
    Logger::trace(std::cout, "Allocating command buffer array", { "CREATE" });
    getHandle().resize(allocateInfo.commandBufferCount);
    if (vkAllocateCommandBuffers(logicalDevice, &allocateInfo,
                                 getHandle().data())
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not allocate command buffer array",
                         { "CREATE" });
    }
    Logger::trace(std::cout, "Allocated command buffer array", { "CREATE" });
}

const VkCommandBuffer &CommandBufferArray::at(uint32_t index)
{
    return getHandle().at(index);
}
