#include <renderer/vulkan/builders/physical-device-builder.hh>

#include <algorithm>
#include <iostream>
#include <sstream>

#include <io/logging/logger.hh>

PhysicalDeviceBuilder::PhysicalDeviceBuilder(const VkInstance &instance,
                                             const VkSurfaceKHR &surface)
    : _instance(instance)
    , _surface(surface)
{
    base();
}

PhysicalDeviceBuilder &PhysicalDeviceBuilder::base()
{
    return *this;
}

PhysicalDeviceType PhysicalDeviceBuilder::build()
{
    std::multimap<int, std::unique_ptr<PhysicalDevice>> deviceMap =
        _ratePhysicalDevices();

    std::ostringstream oss;
    oss << "Best physical device has suitability score "
        << deviceMap.rbegin()->first << "\n";
    Logger::info(std::cout, oss.str(), { "CREATE" });

    if (deviceMap.rbegin()->first > 0)
    {
        Logger::trace(std::cout, "Picking best physical device", { "CREATE" });
    }
    else
    {
        Logger::critical(std::cout,
                         "No physical device has a positive suitability score",
                         { "CREATE" });
    }
    return std::move(deviceMap.rbegin()->second);
}

PhysicalDeviceBuilder &PhysicalDeviceBuilder::withDeviceExtensions(
    const std::vector<const char *> &extensions)
{
    _deviceExtensions = extensions;
    return *this;
}

std::vector<PhysicalDeviceType>
PhysicalDeviceBuilder::_getAvailablePhysicalDevices()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        Logger::critical(std::cout, "Found no GPU with Vulkan support",
                         { "CREATE" });
        throw std::runtime_error("Failed to find a GPU with Vulkan support.");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());
    std::vector<PhysicalDeviceType> physicalDevices;
    for (const auto &device : devices)
    {
        physicalDevices.emplace_back(std::make_unique<PhysicalDevice>(
            device, _surface, _deviceExtensions));
    }
    return physicalDevices;
}

bool PhysicalDeviceBuilder::_isDeviceSuitable(const PhysicalDevice &device)
{
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device.getHandle(), &deviceFeatures);

    if (!deviceFeatures.geometryShader || !deviceFeatures.tessellationShader)
    {
        return false;
    }
    QueueFamilyIndices indices = device.findQueueFamilies();
    bool extensionsSupported = device.checkDeviceExtensionSupport();
    bool swapChainAdequate = false;
    if (extensionsSupported)
    {
        SwapChainSupportDetails swapChainSupport =
            device.querySwapChainSupport();
        swapChainAdequate = swapChainSupport.isValid();
    }
    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

int PhysicalDeviceBuilder::_getDeviceSuitability(const PhysicalDevice &device)
{
    if (!_isDeviceSuitable(device))
    {
        return 0;
    }
    int score = 0;
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device.getHandle(), &deviceProperties);

    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
        score += 1000;
    }
    score += deviceProperties.limits.maxImageDimension2D;
    return score;
}

std::multimap<int, PhysicalDeviceType>
PhysicalDeviceBuilder::_ratePhysicalDevices()
{
    std::vector<PhysicalDeviceType> devices = _getAvailablePhysicalDevices();
    std::multimap<int, PhysicalDeviceType> candidates;

    for (auto &device : devices)
    {
        candidates.emplace(_getDeviceSuitability(*device), std::move(device));
        // can't use devices anymore
    }
    return candidates;
}
