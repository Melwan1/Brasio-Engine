#include <io/debug/vulkan-renderer-debug-printer.hh>

#include <chrono>
#include <map>

#include <io/escapes/ansi-escapes.hh>

void VulkanRendererDebugPrinter::printDebugMessage(
    std::ostream &ostr, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *callbackData)
{
    static std::map<VkDebugUtilsMessageSeverityFlagBitsEXT, std::string>
        severityToString = {
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT, "DEBUG" },
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT, "INFO" },
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT, "WARN" },
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT, "ERROR" }
        };
    static std::map<VkDebugUtilsMessageTypeFlagsEXT, std::string>
        messageTypeToString = {
            { VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT, "GENERAL" },
            { VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT, "VALIDATION" },
            { VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT, "PERFORMANCE" }
        };
    static std::map<VkDebugUtilsMessageSeverityFlagBitsEXT, int>
        severityToColor = {
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT, 27 },
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT, 46 },
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT, 202 },
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT, 88 }
        };

    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&currentTime);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  now.time_since_epoch())
        % 1000;
    std::ostringstream oss;
    oss << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");

    ostr << FG_ESC(244) << "[" << oss.str() << "."
         << std::format("{:03}", ms.count()) << "]";
    switch (messageSeverity)
    {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        ostr << FG_ESC(27);
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        ostr << FG_ESC(46);
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        ostr << FG_ESC(202);
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        ostr << FG_ESC(88);
        break;
    default:
        ostr << FG_ESC(15);
        break;
    }
    ostr << "[" << severityToString.at(messageSeverity) << "]" << FG_ESC(15)
         << "[" << messageTypeToString.at(messageType) << "] " << ESC_RESET
         << callbackData->pMessage << std::endl;
}
