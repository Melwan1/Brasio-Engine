#include <renderer/vulkan/instance.hh>

#include <iostream>

#include <renderer/vulkan/builders/debug-messenger-builder.hh>

#include <io/logging/logger.hh>

Instance::Instance(const VkInstanceCreateInfo &createInfo)
{
    Logger::trace(std::cout, "Creating Vulkan instance", { "CREATE" });
    _instance = std::make_unique<VkInstance>();
    if (vkCreateInstance(&createInfo, nullptr, _instance.get()) != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create Vulkan instance",
                         { "CREATE" });
    }
    Logger::trace(std::cout, "Created Vulkan instance", { "CREATE" });
    _debugMessenger = DebugMessengerBuilder().withInstance(getHandle()).build();
}

Instance::~Instance()
{
    Logger::trace(std::cout, "Destroying Vulkan instance", { "DESTROY" });
    _debugMessenger.reset();
    vkDestroyInstance(getHandle(), nullptr);
    Logger::trace(std::cout, "Destroyed Vulkan instance", { "DESTROY" });
}

VkInstance &Instance::getHandle()
{
    return *_instance;
}
