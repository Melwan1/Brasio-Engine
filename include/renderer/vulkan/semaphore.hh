#pragma once

#include <vulkan/vulkan_core.h>

class Semaphore
{
public:
    Semaphore(const VkDevice &logicalDevice,
              const VkSemaphoreCreateInfo &createInfo);
    ~Semaphore();

    const VkSemaphore &getHandle() const;
    VkSemaphore &getHandle();

private:
    VkDevice _logicalDevice;
    VkSemaphore _semaphore = VK_NULL_HANDLE;
};
