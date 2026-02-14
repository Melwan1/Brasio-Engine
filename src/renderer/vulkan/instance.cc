#include <renderer/vulkan/instance.hh>

#include <iostream>

#include <renderer/vulkan/builders/debug-messenger-builder.hh>

#include <io/logging/logger.hh>

Instance::Instance(const VkInstanceCreateInfo &createInfo)
    : Handler("instance", [](const VkInstance &instance) {
        vkDestroyInstance(instance, nullptr);
    })
{
    Logger::trace(std::cout, "Creating Vulkan instance", { "CREATE" });
    if (vkCreateInstance(&createInfo, nullptr, &getHandle()) != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create Vulkan instance",
                         { "CREATE" });
    }
    Logger::trace(std::cout, "Created Vulkan instance", { "CREATE" });
    _debugMessenger = DebugMessengerBuilder().withInstance(getHandle()).build();
}
