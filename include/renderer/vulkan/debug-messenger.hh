#pragma once

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>

namespace brasio::renderer::vulkan
{
    class DebugMessenger : public core::Handler<VkDebugUtilsMessengerEXT>
    {
    public:
        DebugMessenger(const VkInstance &instance,
                       const VkDebugUtilsMessengerCreateInfoEXT &createInfo);
    };
} // namespace brasio::renderer::vulkan
