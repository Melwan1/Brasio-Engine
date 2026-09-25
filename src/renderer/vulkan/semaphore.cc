#include <renderer/vulkan/semaphore.hh>

#include <io/logging/logger.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    Semaphore::Semaphore(const VkDevice &logicalDevice,
                         const VkSemaphoreCreateInfo &createInfo)
        : Handler("semaphore", [logicalDevice](const VkSemaphore &semaphore) {
            vkDestroySemaphore(logicalDevice, semaphore, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating semaphore", { "CREATE" });
        BRASIO_VULKAN_CHECK(vkCreateSemaphore(logicalDevice, &createInfo,
                                              nullptr, &getHandle()),
                            "create semaphore", { "CREATE" });
        BRASIO_LOG_TRACE("Created semaphore", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
