#include <renderer/vulkan/fence.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    Fence::Fence(const VulkanRenderer &renderer, const VkFenceCreateInfo &createInfo)
        : Handler("fence", [&renderer](const VkFence &fence) {
            vkDestroyFence(renderer.getLogicalDevice(), fence, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating fence", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreateFence(renderer.getLogicalDevice(), &createInfo, nullptr, &getHandle()),
            "create fence", { "CREATE" });
        BRASIO_LOG_TRACE("Created fence", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
