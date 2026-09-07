#include <renderer/vulkan/device.hh>

namespace brasio::renderer::vulkan {

    Device::Device(PhysicalDevice &physicalDevice, LogicalDevice &logicalDevice)
        : Handler("device", [](const std::pair<PhysicalDevice, LogicalDevice>&) { BRASIO_LOG_TRACE("Nothing to be done to destroy device."); })
        {
            getHandle().first = physicalDevice;
            getHandle().second = logicalDevice;
        }

}
