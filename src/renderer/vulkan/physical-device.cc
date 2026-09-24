#include <renderer/vulkan/physical-device.hh>

#include <set>
#include <string>
#include <vector>

namespace brasio::renderer::vulkan
{
    PhysicalDevice::PhysicalDevice(const VkPhysicalDevice &device,
                                   const VkSurfaceKHR &surface,
                                   const std::vector<const char *> extensions)
        : Handler(device, "physical device",
                  [](const VkPhysicalDevice &) {
                      BRASIO_LOG_TRACE(
                          "Nothing to be done to destroy physical device",
                          { "DESTROY" });
                  })
        , _surface(surface)
        , _deviceExtensions(extensions)
    {}

    const std::vector<const char *> &PhysicalDevice::getDeviceExtensions() const
    {
        return _deviceExtensions;
    }

    std::vector<const char *> &PhysicalDevice::getDeviceExtensions()
    {
        return _deviceExtensions;
    }

    QueueFamilyIndices PhysicalDevice::findQueueFamilies() const
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(getHandle(), &queueFamilyCount,
                                                 nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(getHandle(), &queueFamilyCount,
                                                 queueFamilies.data());

        int i = 0;
        for (const auto &queueFamily : queueFamilies)
        {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.graphicsFamily = i;
            }
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(getHandle(), i, _surface,
                                                 &presentSupport);
            if (presentSupport)
            {
                indices.presentFamily = i;
            }
            i++;
        }
        return indices;
    }

    uint32_t
    PhysicalDevice::findMemoryType(uint32_t typeFilter,
                                   VkMemoryPropertyFlags properties) const
    {
        VkPhysicalDeviceMemoryProperties memoryProperties;
        vkGetPhysicalDeviceMemoryProperties(getHandle(), &memoryProperties);

        for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
        {
            if ((typeFilter & (1 << i))
                && (memoryProperties.memoryTypes[i].propertyFlags & properties)
                    == properties)
            {
                BRASIO_LOG_DEBUG("Found memory type: " + std::to_string(i),
                                 { "DEVICE" });
                return i;
            }
        }

        BRASIO_LOG_CRITICAL("No suitable memory type has been found",
                            { "DEVICE" });
        return -1;
    }

    bool PhysicalDevice::checkDeviceExtensionSupport() const
    {
        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(getHandle(), nullptr,
                                             &extensionCount, nullptr);
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(
            getHandle(), nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(_deviceExtensions.begin(),
                                                 _deviceExtensions.end());

        for (const auto &availableExtension : availableExtensions)
        {
            requiredExtensions.erase(availableExtension.extensionName);
        }

        return requiredExtensions.empty();
    }

    SwapChainSupportDetails PhysicalDevice::querySwapChainSupport() const
    {
        SwapChainSupportDetails details;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(getHandle(), _surface,
                                                  &details.capabilities);
        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(getHandle(), _surface,
                                             &formatCount, nullptr);

        if (formatCount > 0)
        {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(
                getHandle(), _surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(getHandle(), _surface,
                                                  &presentModeCount, nullptr);

        if (presentModeCount > 0)
        {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(
                getHandle(), _surface, &presentModeCount,
                details.presentModes.data());
        }

        return details;
    }

    VkFormat
    PhysicalDevice::findSupportedFormat(const std::vector<VkFormat> &candidates,
                                        VkImageTiling tiling,
                                        VkFormatFeatureFlags features) const
    {
        for (const VkFormat &format : candidates)
        {
            VkFormatProperties formatProperties;
            vkGetPhysicalDeviceFormatProperties(getHandle(), format,
                                                &formatProperties);

            if (tiling == VK_IMAGE_TILING_LINEAR
                && (formatProperties.linearTilingFeatures & features)
                    == features)
            {
                return format;
            }
            if (tiling == VK_IMAGE_TILING_OPTIMAL
                && (formatProperties.optimalTilingFeatures & features)
                    == features)
            {
                return format;
            }
        }
        BRASIO_LOG_CRITICAL("No supported format found", { "DEVICE" });
        return VK_FORMAT_D16_UNORM; // placeholder for compilation
    }

    VkFormat PhysicalDevice::findDepthFormat() const
    {
        return findSupportedFormat(
            { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT,
              VK_FORMAT_D24_UNORM_S8_UINT },
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
    }

    bool PhysicalDevice::hasStencilComponent(VkFormat format) const
    {
        return format == VK_FORMAT_D32_SFLOAT_S8_UINT
            || format == VK_FORMAT_D24_UNORM_S8_UINT;
    }

    VkSampleCountFlagBits PhysicalDevice::getMaxUsableSampleCount() const
    {
        VkPhysicalDeviceProperties physicalDeviceProperties;
        vkGetPhysicalDeviceProperties(getHandle(), &physicalDeviceProperties);

        VkSampleCountFlags counts =
            physicalDeviceProperties.limits.framebufferColorSampleCounts
            & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
        std::vector<VkSampleCountFlagBits> countOptionVector = {
            VK_SAMPLE_COUNT_64_BIT, VK_SAMPLE_COUNT_32_BIT,
            VK_SAMPLE_COUNT_16_BIT, VK_SAMPLE_COUNT_8_BIT,
            VK_SAMPLE_COUNT_4_BIT,  VK_SAMPLE_COUNT_2_BIT,
            VK_SAMPLE_COUNT_1_BIT
        };
        for (VkSampleCountFlagBits countOption : countOptionVector)
        {
            if (counts & countOption)
            {
                BRASIO_LOG_TRACE("Setting MSAA samples to "
                                     + std::to_string(static_cast<unsigned int>(
                                         countOption)),
                                 { "DEVICE", "MSAA" });
                return countOption;
            }
        }
        BRASIO_LOG_TRACE("Setting MSAA samples to 1", { "DEVICE", "MSAA" });
        return VK_SAMPLE_COUNT_1_BIT;
    }

} // namespace brasio::renderer::vulkan
