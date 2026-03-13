#pragma once

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>

class Semaphore : public Handler<VkSemaphore>
{
public:
    Semaphore(const VkDevice &logicalDevice,
              const VkSemaphoreCreateInfo &createInfo);
};
