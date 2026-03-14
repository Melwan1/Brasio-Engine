#include <io/debug/vulkan-renderer-debug-printer.hh>

#include <map>

#include <io/logging/logger.hh>

namespace brasio::io::debug
{
    void VulkanRendererDebugPrinter::printDebugMessage(
        std::ostream &ostr,
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT *callbackData)
    {
        static std::map<VkDebugUtilsMessageSeverityFlagBitsEXT,
                        io::logging::LogLevel>
            severityToLevel = {
                { VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT,
                  io::logging::LogLevel::DEBUG },
                { VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
                  io::logging::LogLevel::INFO },
                { VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT,
                  io::logging::LogLevel::WARNING },
                { VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
                  io::logging::LogLevel::ERROR }
            };
        static std::map<VkDebugUtilsMessageTypeFlagsEXT, std::string>
            messageTypeToString = {
                { VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT, "GENERAL" },
                { VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
                  "VALIDATION" },
                { VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
                  "PERFORMANCE" }
            };

        io::logging::LogLevel logLevel = severityToLevel.at(messageSeverity);
        std::string tag = messageTypeToString.at(messageType);
        io::logging::Logger::log(ostr, callbackData->pMessage, logLevel,
                                 { tag });
    }
} // namespace brasio::io::debug
