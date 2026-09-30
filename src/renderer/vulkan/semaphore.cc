#include <renderer/vulkan/semaphore.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    Semaphore::Semaphore(const VulkanRenderer &renderer, const VkSemaphoreCreateInfo &createInfo)
        : Handler("semaphore", [&renderer](const VkSemaphore &semaphore) {
            vkDestroySemaphore(renderer.getLogicalDevice(), semaphore, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating semaphore", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreateSemaphore(renderer.getLogicalDevice(), &createInfo, nullptr, &getHandle()),
            "create semaphore", { "CREATE" });
        BRASIO_LOG_TRACE("Created semaphore", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
