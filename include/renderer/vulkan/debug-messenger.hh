#pragma once

#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan
{
    class DebugMessenger
    {
    public:
        DebugMessenger(const VkInstance &instance,
                       const VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        ~DebugMessenger();

    private:
        VkInstance _instance;
        VkDebugUtilsMessengerEXT _messenger;
    };
} // namespace brasio::renderer::vulkan
