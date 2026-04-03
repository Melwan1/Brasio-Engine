#include <renderer/vulkan/debug-messenger.hh>

#include <iostream>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan
{
    void destroyDebugMessenger(const VkInstance &instance,
                               const VkDebugUtilsMessengerEXT &debugMessenger)
    {
        BRASIO_LOG_TRACE(std::cout, "Destroying debug messenger",
                         { "DESTROY" });
        auto function = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
        if (function != nullptr)
        {
            BRASIO_LOG_TRACE(
                std::cout,
                "Vulkan function found for destroying the debug messenger",
                { "DESTROY" });
            function(instance, debugMessenger, nullptr);
        }
        else
        {
            BRASIO_LOG_WARNING(
                std::cout,
                "Vulkan function NOT found for destroying the debug "
                "messenger, skipping",
                { "DESTROY" });
        }
        BRASIO_LOG_TRACE(std::cout, "Destroyed debug messenger", { "DESTROY" });
    }

    DebugMessenger::DebugMessenger(
        const VkInstance &instance,
        const VkDebugUtilsMessengerCreateInfoEXT &createInfo)
        : Handler("debug messenger",
                  [instance](const VkDebugUtilsMessengerEXT &debugMessenger) {
                      destroyDebugMessenger(instance, debugMessenger);
                  })
    {
        BRASIO_LOG_TRACE(std::cout, "Creating debug messenger", { "CREATE" });
        auto function = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
        if (function != nullptr)
        {
            BRASIO_LOG_TRACE(
                std::cout,
                "Vulkan function found for creating the debug messenger",
                { "CREATE" });
            function(instance, &createInfo, nullptr, &getHandle());
        }
        else
        {
            BRASIO_LOG_WARNING(
                std::cout,
                "Vulkan function NOT found for creating the debug "
                "messenger, skipping",
                { "CREATE" });
        }
        BRASIO_LOG_TRACE(std::cout, "Created debug messenger", { "CREATE" });
    }

} // namespace brasio::renderer::vulkan
