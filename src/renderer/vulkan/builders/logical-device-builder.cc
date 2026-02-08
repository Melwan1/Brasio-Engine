#include <renderer/vulkan/builders/logical-device-builder.hh>

#include <set>

LogicalDeviceBuilder::LogicalDeviceBuilder(const PhysicalDevice &physicalDevice)
    : _physicalDevice(physicalDevice)
    , _queuePriority(1.0f)
{
    base();
}

LogicalDeviceBuilder &LogicalDeviceBuilder::base()
{
    _indices = _physicalDevice.findQueueFamilies();
    std::set<uint32_t> uniqueQueueFamilies = { _indices.graphicsFamily.value(),
                                               _indices.presentFamily.value() };
    for (const uint32_t queueFamilyIndex : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &_queuePriority;
        _queueCreateInfos.emplace_back(queueCreateInfo);
    }
    _validationLayers.clear();
    return *this;
}

LogicalDeviceBuilder &LogicalDeviceBuilder::withValidationLayers(
    const std::vector<const char *> validationLayers)
{
    _validationLayers = validationLayers;
    return *this;
}

LogicalDeviceType LogicalDeviceBuilder::build()
{
    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = _queueCreateInfos.data();
    createInfo.queueCreateInfoCount =
        static_cast<uint32_t>(_queueCreateInfos.size());
    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount =
        static_cast<uint32_t>(_physicalDevice.getDeviceExtensions().size());
    createInfo.ppEnabledExtensionNames =
        _physicalDevice.getDeviceExtensions().data();

    if (_validationLayers.empty())
    {
        createInfo.enabledLayerCount = 0;
    }
    else
    {
        createInfo.enabledLayerCount =
            static_cast<uint32_t>(_validationLayers.size());
        createInfo.ppEnabledLayerNames = _validationLayers.data();
    }

    return std::make_unique<LogicalDevice>(_physicalDevice, createInfo,
                                           _indices);
}
