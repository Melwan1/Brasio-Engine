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
        BRASIO_LOG_TRACE(std::cout, "Creating command pool", { "CREATE" });
        if (vkCreateCommandPool(logicalDevice, &createInfo, nullptr,
                                &getHandle())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL(std::cout, "Could not create command pool",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE(std::cout, "Created command pool", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
