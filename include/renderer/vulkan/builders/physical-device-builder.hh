#pragma once

#include <map>
#include <vector>

#include <vulkan/vulkan_core.h>

#include <core/builder.hh>
#include <renderer/vulkan/physical-device.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;
}

namespace brasio::renderer::vulkan::builders
{
    class PhysicalDeviceBuilder : public core::Builder<PhysicalDeviceType>
    {
    public:
        PhysicalDeviceBuilder(const VulkanRenderer &renderer);

        virtual PhysicalDeviceType build() override;
        virtual PhysicalDeviceBuilder &base() override;

        PhysicalDeviceBuilder &withDeviceExtensions(const std::vector<const char *> &extensions);

        PhysicalDeviceBuilder &
        withValidationLayers(const std::vector<const char *> validationLayers);

    private:
        const VulkanRenderer &_renderer;

        std::vector<const char *> _deviceExtensions;
        std::vector<const char *> _validationLayers;

        std::vector<PhysicalDeviceType> _getAvailablePhysicalDevices();
        bool _isDeviceSuitable(const PhysicalDevice &device);
        int _getDeviceSuitability(const PhysicalDevice &device);

        std::multimap<int, PhysicalDeviceType> _ratePhysicalDevices();
    };
} // namespace brasio::renderer::vulkan::builders
