#include <renderer/vulkan/semaphore.hh>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan
{
    Semaphore::Semaphore(const VkDevice &logicalDevice,
                         const VkSemaphoreCreateInfo &createInfo)
        : Handler("semaphore", [logicalDevice](const VkSemaphore &semaphore) {
            vkDestroySemaphore(logicalDevice, semaphore, nullptr);
        })
    {
        io::logging::Logger::trace(std::cout, "Creating semaphore",
                                   { "CREATE" });
        if (vkCreateSemaphore(logicalDevice, &createInfo, nullptr, &getHandle())
            != VK_SUCCESS)
        {
            io::logging::Logger::critical(
                std::cout, "Could not create semaphore", { "CREATE" });
        }
        io::logging::Logger::trace(std::cout, "Created semaphore",
                                   { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
