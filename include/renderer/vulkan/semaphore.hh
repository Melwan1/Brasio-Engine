#pragma once

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class Semaphore : public core::Handler<VkSemaphore>
    {
    public:
        Semaphore(const VulkanRenderer &renderer, const VkSemaphoreCreateInfo &createInfo);
    };
} // namespace brasio::renderer::vulkan
