#pragma once

#include <vulkan/vulkan_core.h>

class Fence
{
public:
    Fence(const VkDevice &logicalDevice, const VkFenceCreateInfo &createInfo);
    ~Fence();

    const VkFence &getHandle() const;
    VkFence &getHandle();

private:
    VkDevice _logicalDevice;
    VkFence _fence = VK_NULL_HANDLE;
};
