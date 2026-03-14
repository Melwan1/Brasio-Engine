#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/debug-messenger.hh>
#include <core/handler.hh>

namespace brasio::renderer::vulkan
{

    class Instance : public core::Handler<VkInstance>
    {
    public:
        Instance(const VkInstanceCreateInfo &createInfo);

    private:
        std::unique_ptr<DebugMessenger> _debugMessenger;
    };

    using InstanceType = std::unique_ptr<Instance>;
} // namespace brasio::renderer::vulkan
