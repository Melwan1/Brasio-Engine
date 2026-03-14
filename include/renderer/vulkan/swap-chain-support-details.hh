#pragma once

#include <vector>

#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan
{
    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;

        bool isValid() const;
    };
} // namespace brasio::renderer::vulkan
