#include <renderer/vulkan/command-pool.hh>

namespace brasio::renderer::vulkan
{
    CommandPool::CommandPool(const VkDevice &logicalDevice,
                             const VkCommandPoolCreateInfo &createInfo)
        : Handler("command pool",
                  [logicalDevice](const VkCommandPool &commandPool) {
                      vkDestroyCommandPool(logicalDevice, commandPool, nullptr);
                  })
    {
        io::logging::Logger::trace(std::cout, "Creating command pool",
                                   { "CREATE" });
        if (vkCreateCommandPool(logicalDevice, &createInfo, nullptr,
                                &getHandle())
            != VK_SUCCESS)
        {
            io::logging::Logger::critical(
                std::cout, "Could not create command pool", { "CREATE" });
        }
        io::logging::Logger::trace(std::cout, "Created command pool",
                                   { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
