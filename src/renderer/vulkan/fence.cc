#include <renderer/vulkan/fence.hh>

#include <io/logging/logger.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    Fence::Fence(const VkDevice &logicalDevice,
                 const VkFenceCreateInfo &createInfo)
        : Handler("fence", [logicalDevice](const VkFence &fence) {
            vkDestroyFence(logicalDevice, fence, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating fence", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreateFence(logicalDevice, &createInfo, nullptr, &getHandle()),
            "create fence", { "CREATE" });
        BRASIO_LOG_TRACE("Created fence", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
