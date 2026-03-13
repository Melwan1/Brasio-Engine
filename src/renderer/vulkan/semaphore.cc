#include <renderer/vulkan/semaphore.hh>

#include <io/logging/logger.hh>

Semaphore::Semaphore(const VkDevice &logicalDevice,
                     const VkSemaphoreCreateInfo &createInfo)
    : Handler("semaphore", [logicalDevice](const VkSemaphore &semaphore) {
        vkDestroySemaphore(logicalDevice, semaphore, nullptr);
    })
{
    Logger::trace(std::cout, "Creating semaphore", { "CREATE" });
    if (vkCreateSemaphore(logicalDevice, &createInfo, nullptr, &getHandle())
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create semaphore", { "CREATE" });
    }
    Logger::trace(std::cout, "Created semaphore", { "CREATE" });
}
