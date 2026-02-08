#pragma once

#include <memory>
#include <vector>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/queue-family-indices.hh>
#include <renderer/vulkan/swap-chain-support-details.hh>

class PhysicalDevice
{
public:
    PhysicalDevice(const VkPhysicalDevice &device, const VkSurfaceKHR &surface,
                   std::vector<const char *> extensions = {});
    ~PhysicalDevice();

    const VkPhysicalDevice &getHandle() const;
    VkPhysicalDevice &getHandle();

    const std::vector<const char *> &getDeviceExtensions() const;
    std::vector<const char *> &getDeviceExtensions();

    QueueFamilyIndices findQueueFamilies() const;
    bool checkDeviceExtensionSupport() const;
    SwapChainSupportDetails querySwapChainSupport() const;

private:
    VkPhysicalDevice _device;
    VkSurfaceKHR _surface;
    std::vector<const char *> _deviceExtensions;
};

using PhysicalDeviceType = std::unique_ptr<PhysicalDevice>;
