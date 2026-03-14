#include <renderer/vulkan/debug-messenger.hh>

#include <iostream>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan
{
    DebugMessenger::DebugMessenger(
        const VkInstance &instance,
        const VkDebugUtilsMessengerCreateInfoEXT &createInfo)
        : _instance(instance)
    {
        io::logging::Logger::trace(std::cout, "Creating debug messenger",
                                   { "CREATE" });
        auto function = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
        if (function != nullptr)
        {
            io::logging::Logger::trace(
                std::cout,
                "Vulkan function found for creating the debug messenger",
                { "CREATE" });
            function(_instance, &createInfo, nullptr, &_messenger);
        }
        else
        {
            io::logging::Logger::warning(
                std::cout,
                "Vulkan function NOT found for creating the debug "
                "messenger, skipping",
                { "CREATE" });
        }
        io::logging::Logger::trace(std::cout, "Created debug messenger",
                                   { "CREATE" });
    }

    DebugMessenger::~DebugMessenger()
    {
        io::logging::Logger::trace(std::cout, "Destroying debug messenger",
                                   { "DESTROY" });
        auto function = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(_instance,
                                  "vkDestroyDebugUtilsMessengerEXT"));
        if (function != nullptr)
        {
            io::logging::Logger::trace(
                std::cout,
                "Vulkan function found for destroying the debug messenger",
                { "DESTROY" });
            function(_instance, _messenger, nullptr);
        }
        else
        {
            io::logging::Logger::warning(
                std::cout,
                "Vulkan function NOT found for destroying the debug "
                "messenger, skipping",
                { "DESTROY" });
        }
        io::logging::Logger::trace(std::cout, "Destroyed debug messenger",
                                   { "DESTROY" });
    }
} // namespace brasio::renderer::vulkan
