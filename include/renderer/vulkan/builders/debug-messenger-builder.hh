#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <core/builder.hh>
#include <renderer/vulkan/debug-messenger.hh>

using DebugMessengerType = std::unique_ptr<DebugMessenger>;

class DebugMessengerBuilder : public Builder<DebugMessengerType>
{
public:
    DebugMessengerBuilder();

    virtual DebugMessengerBuilder &base() override;
    DebugMessengerBuilder &withInstance(VkInstance &instance);
    virtual DebugMessengerType build() override;
    VkDebugUtilsMessengerCreateInfoEXT getCreateInfo() const;

private:
    VkInstance _instance;

    VkStructureType _structureType;
    VkDebugUtilsMessageSeverityFlagsEXT _messageSeverity;
    VkDebugUtilsMessageTypeFlagsEXT _messageType;
    PFN_vkDebugUtilsMessengerCallbackEXT _userCallback;
};
