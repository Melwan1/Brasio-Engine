#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/debug-messenger.hh>
#include <core/handler.hh>

class Instance : public Handler<VkInstance>
{
public:
    Instance(const VkInstanceCreateInfo &createInfo);

private:
    std::unique_ptr<DebugMessenger> _debugMessenger;
};
