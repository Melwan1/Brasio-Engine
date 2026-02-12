#include <renderer/vulkan/semaphore.hh>

#include <io/logging/logger.hh>

Semaphore::Semaphore(const VkDevice &logicalDevice,
                     const VkSemaphoreCreateInfo &createInfo)
    : _logicalDevice(logicalDevice)
{
    Logger::trace(std::cout, "Creating semaphore", { "CREATE" });
    if (vkCreateSemaphore(_logicalDevice, &createInfo, nullptr, &_semaphore)
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create semaphore", { "CREATE" });
    }
    Logger::trace(std::cout, "Created semaphore", { "CREATE" });
}

Semaphore::~Semaphore()
{
    Logger::trace(std::cout, "Destroying semaphore", { "DESTROY" });
    vkDestroySemaphore(_logicalDevice, _semaphore, nullptr);
    Logger::trace(std::cout, "Destroyed semaphore", { "DESTROY" });
}

const VkSemaphore &Semaphore::getHandle() const
{
    return _semaphore;
}

VkSemaphore &Semaphore::getHandle()
{
    return _semaphore;
}
