#include <renderer/vulkan/instance.hh>

#include <iostream>

#include <renderer/vulkan/builders/debug-messenger-builder.hh>

#include <io/logging/logger.hh>

Instance::Instance(const VkInstanceCreateInfo &createInfo)
{
    Logger::trace(std::cout, "Creating Vulkan instance.");
    _instance = std::make_unique<VkInstance>();
    if (vkCreateInstance(&createInfo, nullptr, _instance.get()) != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create Vulkan instance");
    }
    Logger::trace(std::cout, "Successfully created Vulkan instance.");
    _debugMessenger = DebugMessengerBuilder().withInstance(getHandle()).build();
}

Instance::~Instance()
{
    _debugMessenger.reset();
    vkDestroyInstance(getHandle(), nullptr);
}

VkInstance &Instance::getHandle()
{
    return *_instance;
}
