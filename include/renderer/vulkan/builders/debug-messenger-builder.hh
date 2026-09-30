#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <core/builder.hh>
#include <renderer/vulkan/debug-messenger.hh>

namespace brasio::renderer::vulkan::builders
{
    using DebugMessengerType = std::unique_ptr<DebugMessenger>;

    class DebugMessengerBuilder : public core::Builder<DebugMessengerType>
    {
    public:
        DebugMessengerBuilder(VkInstance instance);

        virtual DebugMessengerBuilder &base() override;
        virtual DebugMessengerType build() override;
        VkDebugUtilsMessengerCreateInfoEXT getCreateInfo() const;

    private:
        VkInstance _instance;

        VkStructureType _structureType;
        VkDebugUtilsMessageSeverityFlagsEXT _messageSeverity;
        VkDebugUtilsMessageTypeFlagsEXT _messageType;
        PFN_vkDebugUtilsMessengerCallbackEXT _userCallback;
    };
} // namespace brasio::renderer::vulkan::builders
