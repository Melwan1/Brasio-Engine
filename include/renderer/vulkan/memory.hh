#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/physical-device.hh>

#include <memory>

namespace brasio::renderer::vulkan
{
    class Buffer;
    class Texture;

    class Memory : public core::Handler<VkDeviceMemory>
    {
    public:
        Memory(const PhysicalDeviceType &physicalDevice,
               const VkDevice &logicalDevice, const Buffer &buffer,
               VkMemoryPropertyFlags memoryProperties, void *data, size_t size);

        Memory(const PhysicalDeviceType &physicalDevice,
               const VkDevice &logicalDevice, const Texture &texture,
               VkMemoryPropertyFlags memoryProperties);

        void allocate(const PhysicalDeviceType &physicalDevice,
                      const VkDevice &logicalDevice,
                      const VkMemoryPropertyFlags &memoryProperties,
                      const VkMemoryRequirements &memoryRequirements);

        void map();
        void unmap();
        void setContent(const void *content);

    private:
        VkDevice _logicalDevice;
        size_t _size;
        void *_deviceData;
    };

    using MemoryType = std::unique_ptr<Memory>;
} // namespace brasio::renderer::vulkan
