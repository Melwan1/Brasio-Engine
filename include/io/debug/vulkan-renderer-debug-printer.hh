#pragma once

#include <vulkan/vulkan.hpp>

#include <ostream>

class VulkanRendererDebugPrinter
{
public:
    static void
    printDebugMessage(std::ostream &ostr,
                      VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                      VkDebugUtilsMessageTypeFlagsEXT messageType,
                      const VkDebugUtilsMessengerCallbackDataEXT *callbackData);
};
