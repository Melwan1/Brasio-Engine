#include <renderer/vulkan/fence.hh>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan
{
    Fence::Fence(const VkDevice &logicalDevice,
                 const VkFenceCreateInfo &createInfo)
        : Handler("fence", [logicalDevice](const VkFence &fence) {
            vkDestroyFence(logicalDevice, fence, nullptr);
        })
    {
        BRASIO_LOG_TRACE(std::cout, "Creating fence", { "CREATE" });
        if (vkCreateFence(logicalDevice, &createInfo, nullptr, &getHandle())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL(std::cout, "Could not create fence",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE(std::cout, "Created fence", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
