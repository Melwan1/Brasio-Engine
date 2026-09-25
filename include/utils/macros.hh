#pragma once

#include <vulkan/vulkan_core.h>
#include <io/logging/logger.hh>

#define BRASIO_VULKAN_CHECK(command_result, fail_message, fail_tags)                               \
    do                                                                                             \
    {                                                                                              \
        if (command_result != VK_SUCCESS)                                                          \
        {                                                                                          \
            BRASIO_LOG_CRITICAL(std::string("Failed to ") + fail_message, fail_tags);              \
        }                                                                                          \
    } while (0)
