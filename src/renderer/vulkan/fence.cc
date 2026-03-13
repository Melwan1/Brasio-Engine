#include <renderer/vulkan/fence.hh>

#include <io/logging/logger.hh>

Fence::Fence(const VkDevice &logicalDevice, const VkFenceCreateInfo &createInfo)
    : Handler("fence", [logicalDevice](const VkFence &fence) {
        vkDestroyFence(logicalDevice, fence, nullptr);
    })
{
    Logger::trace(std::cout, "Creating fence", { "CREATE" });
    if (vkCreateFence(logicalDevice, &createInfo, nullptr, &getHandle())
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create fence", { "CREATE" });
    }
    Logger::trace(std::cout, "Created fence", { "CREATE" });
}
