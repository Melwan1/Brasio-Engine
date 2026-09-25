#include <renderer/vulkan/command-pool.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    CommandPool::CommandPool(const VkDevice &logicalDevice,
                             const VkCommandPoolCreateInfo &createInfo)
        : Handler("command pool",
                  [logicalDevice](const VkCommandPool &commandPool) {
                      vkDestroyCommandPool(logicalDevice, commandPool, nullptr);
                  })
    {
        BRASIO_LOG_TRACE("Creating command pool", { "CREATE" });
        BRASIO_VULKAN_CHECK(vkCreateCommandPool(logicalDevice, &createInfo,
                                                nullptr, &getHandle()),
                            "create command pool", { "CREATE" });
        BRASIO_LOG_TRACE("Created command pool", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
