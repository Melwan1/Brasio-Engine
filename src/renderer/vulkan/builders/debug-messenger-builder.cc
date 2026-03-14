#include <renderer/vulkan/builders/debug-messenger-builder.hh>

#include <iostream>

#include <io/debug/vulkan-renderer-debug-printer.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{
    static VKAPI_ATTR VkBool32 VKAPI_CALL
    debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                  VkDebugUtilsMessageTypeFlagsEXT messageType,
                  const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
                  void *userData)
    {
        (void)userData;
        io::debug::VulkanRendererDebugPrinter::printDebugMessage(
            std::cout, messageSeverity, messageType, callbackData);
        return VK_FALSE;
    }

    DebugMessengerBuilder::DebugMessengerBuilder()
    {
        _instance = VK_NULL_HANDLE;
        base();
    }

    DebugMessengerBuilder &DebugMessengerBuilder::base()
    {
        _structureType =
            VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        _messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        _messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
        _userCallback = debugCallback;
        return *this;
    }

    DebugMessengerBuilder &
    DebugMessengerBuilder::withInstance(VkInstance &instance)
    {
        _instance = instance;
        return *this;
    }

    DebugMessengerType DebugMessengerBuilder::build()
    {
        VkDebugUtilsMessengerCreateInfoEXT createInfo = getCreateInfo();
        return std::make_unique<DebugMessenger>(_instance, createInfo);
    }

    VkDebugUtilsMessengerCreateInfoEXT
    DebugMessengerBuilder::getCreateInfo() const
    {
        VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
        createInfo.sType = _structureType;
        createInfo.messageSeverity = _messageSeverity;
        createInfo.messageType = _messageType;
        createInfo.pfnUserCallback = _userCallback;
        createInfo.pUserData = nullptr;
        createInfo.pNext = nullptr;
        return createInfo;
    }

} // namespace brasio::renderer::vulkan::builders
