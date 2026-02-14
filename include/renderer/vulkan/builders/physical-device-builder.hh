#pragma once

#include <map>
#include <vector>

#include <vulkan/vulkan_core.h>

#include <core/builder.hh>
#include <renderer/vulkan/physical-device.hh>

class PhysicalDeviceBuilder : public Builder<PhysicalDeviceType>
{
public:
    PhysicalDeviceBuilder(const VkInstance &instance,
                          const VkSurfaceKHR &surface);

    virtual PhysicalDeviceType build() override;
    virtual PhysicalDeviceBuilder &base() override;

    PhysicalDeviceBuilder &
    withDeviceExtensions(const std::vector<const char *> &extensions);

private:
    VkInstance _instance;
    VkSurfaceKHR _surface;

    std::vector<const char *> _deviceExtensions;

    std::vector<PhysicalDeviceType> _getAvailablePhysicalDevices();
    bool _isDeviceSuitable(const PhysicalDevice &device);
    int _getDeviceSuitability(const PhysicalDevice &device);

    std::multimap<int, PhysicalDeviceType> _ratePhysicalDevices();
};
