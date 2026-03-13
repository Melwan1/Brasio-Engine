#include <renderer/vulkan/command-pool.hh>

CommandPool::CommandPool(const VkDevice &logicalDevice,
                         const VkCommandPoolCreateInfo &createInfo)
    : Handler("command pool",
              [logicalDevice](const VkCommandPool &commandPool) {
                  vkDestroyCommandPool(logicalDevice, commandPool, nullptr);
              })
{
    Logger::trace(std::cout, "Creating command pool", { "CREATE" });
    if (vkCreateCommandPool(logicalDevice, &createInfo, nullptr, &getHandle())
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create command pool",
                         { "CREATE" });
    }
    Logger::trace(std::cout, "Created command pool", { "CREATE" });
}
