#pragma once

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/physical-device.hh>

class LogicalDevice
{
public:
    LogicalDevice(const PhysicalDevice &physicalDevice,
                  const VkDeviceCreateInfo &createInfo,
                  const QueueFamilyIndices &indices);
    ~LogicalDevice();

    const VkDevice &getHandle() const;
    VkDevice &getHandle();

    const VkQueue &getGraphicsQueue() const;
    VkQueue &getGraphicsQueue();
    const VkQueue &getPresentationQueue() const;
    VkQueue &getPresentationQueue();

    void waitIdle() const;

private:
    PhysicalDevice _physicalDevice;
    QueueFamilyIndices _queueFamilyIndices;
    VkDevice _device = VK_NULL_HANDLE;

    VkQueue _graphicsQueue = VK_NULL_HANDLE;
    VkQueue _presentationQueue = VK_NULL_HANDLE;
};

using LogicalDeviceType = std::unique_ptr<LogicalDevice>;
