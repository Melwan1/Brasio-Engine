#include <renderer/vulkan/logical-device.hh>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan
{
    LogicalDevice::LogicalDevice(const VkPhysicalDevice &physicalDevice,
                                 const VkDeviceCreateInfo &createInfo,
                                 const QueueFamilyIndices &indices)
        : Handler(
              "logical device",
              [](const VkDevice &device) { vkDestroyDevice(device, nullptr); })
        , _queueFamilyIndices(indices)
    {
        BRASIO_LOG_TRACE(std::cout, "Creating logical device", { "CREATE" });
        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &getHandle())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL(std::cout, "Could not create logical device",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE(std::cout, "Created logical device", { "CREATE" });
        BRASIO_LOG_TRACE(std::cout, "Setting up device queues", { "CREATE" });

        vkGetDeviceQueue(getHandle(),
                         _queueFamilyIndices.graphicsFamily.value(), 0,
                         &_graphicsQueue);
        vkGetDeviceQueue(getHandle(), _queueFamilyIndices.presentFamily.value(),
                         0, &_presentationQueue);
        BRASIO_LOG_TRACE(std::cout, "Set up device queues", { "CREATE" });
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
        BRASIO_LOG_TRACE(std::cout, "Waiting for idle device");
        vkDeviceWaitIdle(getHandle());
        BRASIO_LOG_TRACE(std::cout, "Device is idle");
    }
} // namespace brasio::renderer::vulkan
