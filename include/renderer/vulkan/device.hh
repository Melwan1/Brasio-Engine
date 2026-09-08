#pragma once

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>
#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/physical-device.hh>

namespace brasio::renderer::vulkan {

    class Device : public core::Handler<std::pair<PhysicalDevice, LogicalDevice>> {

        public:

            Device(PhysicalDevice &physicalDevice, LogicalDevice &logicalDevice);

            PhysicalDevice &getPhysicalDevice();
            const PhysicalDevice &getPhysicalDevice() const;

            LogicalDevice &getLogicalDevice();
            const LogicalDevice &getLogicalDevice() const;
    };

}
