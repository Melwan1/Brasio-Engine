#pragma once

#include <memory>
#include <vector>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/queue-family-indices.hh>
#include <renderer/vulkan/swap-chain-support-details.hh>
#include <core/handler.hh>

class PhysicalDevice : public Handler<VkPhysicalDevice>
{
public:
    PhysicalDevice(const VkPhysicalDevice &device, const VkSurfaceKHR &surface,
                   std::vector<const char *> extensions = {});

    const std::vector<const char *> &getDeviceExtensions() const;
    std::vector<const char *> &getDeviceExtensions();

    QueueFamilyIndices findQueueFamilies() const;
    bool checkDeviceExtensionSupport() const;
    SwapChainSupportDetails querySwapChainSupport() const;
    uint32_t findMemoryType(uint32_t typeFilter,
                            VkMemoryPropertyFlags properties) const;

private:
    VkSurfaceKHR _surface;
    std::vector<const char *> _deviceExtensions;
};

using PhysicalDeviceType = std::unique_ptr<PhysicalDevice>;
