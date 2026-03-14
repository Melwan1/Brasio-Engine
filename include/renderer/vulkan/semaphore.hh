#pragma once

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>

namespace brasio::renderer::vulkan
{
    class Semaphore : public core::Handler<VkSemaphore>
    {
    public:
        Semaphore(const VkDevice &logicalDevice,
                  const VkSemaphoreCreateInfo &createInfo);
    };
} // namespace brasio::renderer::vulkan
