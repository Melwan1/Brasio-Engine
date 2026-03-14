#pragma once

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/physical-device.hh>
#include <core/handler.hh>

namespace brasio::renderer::vulkan
{
    class LogicalDevice : public core::Handler<VkDevice>
    {
    public:
        LogicalDevice(const VkPhysicalDevice &physicalDevice,
                      const VkDeviceCreateInfo &createInfo,
                      const QueueFamilyIndices &indices);

        const VkQueue &getGraphicsQueue() const;
        VkQueue &getGraphicsQueue();
        const VkQueue &getPresentationQueue() const;
        VkQueue &getPresentationQueue();

        void waitIdle() const;

    private:
        QueueFamilyIndices _queueFamilyIndices;

        VkQueue _graphicsQueue = VK_NULL_HANDLE;
        VkQueue _presentationQueue = VK_NULL_HANDLE;
    };

    using LogicalDeviceType = std::unique_ptr<LogicalDevice>;
} // namespace brasio::renderer::vulkan
