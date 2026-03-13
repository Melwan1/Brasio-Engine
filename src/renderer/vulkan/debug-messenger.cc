#include <renderer/vulkan/debug-messenger.hh>

#include <iostream>

#include <io/logging/logger.hh>

DebugMessenger::DebugMessenger(
    const VkInstance &instance,
    const VkDebugUtilsMessengerCreateInfoEXT &createInfo)
    : _instance(instance)
{
    Logger::trace(std::cout, "Creating debug messenger", { "CREATE" });
    auto function = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
    if (function != nullptr)
    {
        Logger::trace(std::cout,
                      "Vulkan function found for creating the debug messenger",
                      { "CREATE" });
        function(_instance, &createInfo, nullptr, &_messenger);
    }
    else
    {
        Logger::warning(std::cout,
                        "Vulkan function NOT found for creating the debug "
                        "messenger, skipping",
                        { "CREATE" });
    }
    Logger::trace(std::cout, "Created debug messenger", { "CREATE" });
}

DebugMessenger::~DebugMessenger()
{
    Logger::trace(std::cout, "Destroying debug messenger", { "DESTROY" });
    auto function = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT"));
    if (function != nullptr)
    {
        Logger::trace(
            std::cout,
            "Vulkan function found for destroying the debug messenger",
            { "DESTROY" });
        function(_instance, _messenger, nullptr);
    }
    else
    {
        Logger::warning(std::cout,
                        "Vulkan function NOT found for destroying the debug "
                        "messenger, skipping",
                        { "DESTROY" });
    }
    Logger::trace(std::cout, "Destroyed debug messenger", { "DESTROY" });
}
