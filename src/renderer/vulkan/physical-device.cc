#include <renderer/vulkan/physical-device.hh>

#include <set>
#include <string>
#include <vector>

PhysicalDevice::PhysicalDevice(const VkPhysicalDevice &device,
                               const VkSurfaceKHR &surface,
                               const std::vector<const char *> extensions)
    : _device(device)
    , _surface(surface)
    , _deviceExtensions(extensions)
{}

PhysicalDevice::~PhysicalDevice()
{
    // nothing, a physical device should not be destructed
}

const VkPhysicalDevice &PhysicalDevice::getHandle() const
{
    return _device;
}

VkPhysicalDevice &PhysicalDevice::getHandle()
{
    return _device;
}

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

bool PhysicalDevice::checkDeviceExtensionSupport() const
{
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(getHandle(), nullptr, &extensionCount,
                                         nullptr);
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(getHandle(), nullptr, &extensionCount,
                                         availableExtensions.data());

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
    vkGetPhysicalDeviceSurfaceFormatsKHR(getHandle(), _surface, &formatCount,
                                         nullptr);

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
        vkGetPhysicalDeviceSurfacePresentModesKHR(getHandle(), _surface,
                                                  &presentModeCount,
                                                  details.presentModes.data());
    }

    return details;
}
