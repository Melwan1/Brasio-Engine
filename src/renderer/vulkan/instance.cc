#include <renderer/vulkan/instance.hh>

#include <iostream>

#include <renderer/vulkan/builders/debug-messenger-builder.hh>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan
{
    Instance::Instance(const VkInstanceCreateInfo &createInfo)
        : Handler("instance", [](const VkInstance &instance) {
            vkDestroyInstance(instance, nullptr);
        })
    {
        io::logging::Logger::trace(std::cout, "Creating Vulkan instance",
                                   { "CREATE" });
        if (vkCreateInstance(&createInfo, nullptr, &getHandle()) != VK_SUCCESS)
        {
            io::logging::Logger::critical(
                std::cout, "Could not create Vulkan instance", { "CREATE" });
        }
        io::logging::Logger::trace(std::cout, "Created Vulkan instance",
                                   { "CREATE" });
        _debugMessenger =
            builders::DebugMessengerBuilder().withInstance(getHandle()).build();
    }
} // namespace brasio::renderer::vulkan
