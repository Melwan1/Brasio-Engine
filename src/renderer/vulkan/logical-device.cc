#include <renderer/vulkan/logical-device.hh>

#include <io/logging/logger.hh>

LogicalDevice::LogicalDevice(const PhysicalDevice &physicalDevice,
                             const VkDeviceCreateInfo &createInfo,
                             const QueueFamilyIndices &indices)
    : _physicalDevice(physicalDevice)
    , _queueFamilyIndices(indices)
{
    Logger::trace(std::cout, "Creating logical device", { "CREATE" });
    if (vkCreateDevice(_physicalDevice.getHandle(), &createInfo, nullptr,
                       &_device)
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create logical device",
                         { "CREATE" });
    }
    Logger::trace(std::cout, "Created logical device", { "CREATE" });
    Logger::trace(std::cout, "Setting up device queues", { "CREATE" });

    vkGetDeviceQueue(getHandle(), _queueFamilyIndices.graphicsFamily.value(), 0,
                     &_graphicsQueue);
    vkGetDeviceQueue(getHandle(), _queueFamilyIndices.presentFamily.value(), 0,
                     &_presentationQueue);
    Logger::trace(std::cout, "Set up device queues", { "CREATE" });
}

LogicalDevice::~LogicalDevice()
{
    // no need to destroy device queues
    Logger::trace(std::cout, "Destroying logical device", { "DESTROY" });
    vkDestroyDevice(_device, nullptr);
    Logger::trace(std::cout, "Destroyed logical device", { "DESTROY" });
}

const VkDevice &LogicalDevice::getHandle() const
{
    return _device;
}

VkDevice &LogicalDevice::getHandle()
{
    return _device;
}

const VkQueue &LogicalDevice::getGraphicsQueue() const
{
    return _graphicsQueue;
}

VkQueue &LogicalDevice::getGraphicsQueue()
{
    return _graphicsQueue;
}

const VkQueue &LogicalDevice::getPresentationQueue() const
{
    return _presentationQueue;
}

VkQueue &LogicalDevice::getPresentationQueue()
{
    return _presentationQueue;
}

void LogicalDevice::waitIdle() const
{
    Logger::trace(std::cout, "Waiting for idle device");
    vkDeviceWaitIdle(getHandle());
    Logger::trace(std::cout, "Device is idle");
}
