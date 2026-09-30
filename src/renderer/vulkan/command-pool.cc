#include <renderer/vulkan/command-pool.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    CommandPool::CommandPool(const VulkanRenderer &renderer,
                             const VkCommandPoolCreateInfo &createInfo)
        : Handler("command pool", [&renderer](const VkCommandPool &commandPool) {
            vkDestroyCommandPool(renderer.getLogicalDevice(), commandPool, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating command pool", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreateCommandPool(renderer.getLogicalDevice(), &createInfo, nullptr, &getHandle()),
            "create command pool", { "CREATE" });
        BRASIO_LOG_TRACE("Created command pool", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
