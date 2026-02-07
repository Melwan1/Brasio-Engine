#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/debug-messenger.hh>

class Instance
{
public:
    Instance(const VkInstanceCreateInfo &createInfo);
    ~Instance();

    VkInstance &getHandle();

private:
    std::unique_ptr<VkInstance> _instance;
    std::unique_ptr<DebugMessenger> _debugMessenger;
};
