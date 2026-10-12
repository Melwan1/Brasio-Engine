#pragma once

#include <vulkan/vulkan_core.h>
#include <string>

namespace brasio::utils
{
    std::string vkResultToString(VkResult result);
} // namespace brasio::utils
