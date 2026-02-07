#include <io/debug/vulkan-renderer-debug-printer.hh>

#include <map>

#include <io/logging/logger.hh>

void VulkanRendererDebugPrinter::printDebugMessage(
    std::ostream &ostr, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *callbackData)
{
    static std::map<VkDebugUtilsMessageSeverityFlagBitsEXT, LogLevel>
        severityToLevel = {
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT,
              LogLevel::DEBUG },
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT, LogLevel::INFO },
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT,
              LogLevel::WARNING },
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT, LogLevel::ERROR }
        };
    static std::map<VkDebugUtilsMessageTypeFlagsEXT, std::string>
        messageTypeToString = {
            { VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT, "GENERAL" },
            { VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT, "VALIDATION" },
            { VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT, "PERFORMANCE" }
        };

    LogLevel logLevel = severityToLevel.at(messageSeverity);
    std::string tag = messageTypeToString.at(messageType);
    Logger::log(ostr, callbackData->pMessage, logLevel, { tag });
}
