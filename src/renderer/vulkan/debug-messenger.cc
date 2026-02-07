#include <renderer/vulkan/debug-messenger.hh>

#include <iostream>

#include <io/logging/logger.hh>

DebugMessenger::DebugMessenger(
    const VkInstance &instance,
    const VkDebugUtilsMessengerCreateInfoEXT &createInfo)
    : _instance(instance)
{
    Logger::trace(std::cout, "Creating debug logger", { "LOGGING" });
    auto function = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
    if (function != nullptr)
    {
        Logger::trace(std::cout,
                      "Vulkan function found for creating the debug logger.",
                      { "LOGGING" });
        function(_instance, &createInfo, nullptr, &_messenger);
    }
    else
    {
        Logger::trace(
            std::cout,
            "Vulkan function NOT found for creating the debug logger.",
            { "LOGGING" });
    }
}

DebugMessenger::~DebugMessenger()
{
    auto function = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT"));
    if (function != nullptr)
    {
        function(_instance, _messenger, nullptr);
    }
}
