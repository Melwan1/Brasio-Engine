#pragma once

#include <vector>

#include <vulkan/vulkan_core.h>

#include <core/builder.hh>

#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/physical-device.hh>
#include <renderer/vulkan/queue-family-indices.hh>

namespace brasio::renderer::vulkan::builders
{
    class LogicalDeviceBuilder : public core::Builder<LogicalDeviceType>
    {
    public:
        LogicalDeviceBuilder(const PhysicalDevice &physicalDevice);

        virtual LogicalDeviceBuilder &base() override;

        LogicalDeviceBuilder &
        withValidationLayers(const std::vector<const char *> validationLayers);

        virtual LogicalDeviceType build() override;

    private:
        const PhysicalDevice &_physicalDevice;
        float _queuePriority;
        std::vector<VkDeviceQueueCreateInfo> _queueCreateInfos;
        QueueFamilyIndices _indices;

        std::vector<const char *> _validationLayers;
    };
} // namespace brasio::renderer::vulkan::builders
