#pragma once

#include <vulkan/vulkan.hpp>

#include <ostream>

namespace brasio::io::debug
{
    class VulkanRendererDebugPrinter
    {
    public:
        static void printDebugMessage(
            std::ostream &ostr,
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT *callbackData);
    };
} // namespace brasio::io::debug
