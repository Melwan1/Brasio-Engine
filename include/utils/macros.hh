#pragma once

#include <vulkan/vulkan_core.h>
#include <io/logging/logger.hh>
#include <utils/vk-result.hh>
#include <yaml-cpp/yaml.h>

#define BRASIO_VULKAN_CHECK(command_result, fail_message, fail_tags)                               \
    do                                                                                             \
    {                                                                                              \
        VkResult _brasioVulkanResult = (command_result);                                           \
        if (_brasioVulkanResult != VK_SUCCESS)                                                     \
        {                                                                                          \
            BRASIO_LOG_CRITICAL(std::string("Failed to ") + fail_message + " ("                    \
                                    + brasio::utils::vkResultToString(_brasioVulkanResult) + ")",  \
                                fail_tags);                                                        \
        }                                                                                          \
    } while (0)

#define BRASIO_YAML_ATTRIBUTE(attribute) YAML::Key << #attribute << YAML::Value << attribute
#define BRASIO_YAML_KV(key, value) YAML::Key << #key << YAML::Value << value
