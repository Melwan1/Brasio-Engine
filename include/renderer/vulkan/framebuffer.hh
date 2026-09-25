#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>
#include <renderer/vulkan/logical-device.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    class Framebuffer : public core::Handler<VkFramebuffer>
    {
    public:
        Framebuffer(const LogicalDeviceType &logicalDevice,
                    const VkFramebufferCreateInfo &createInfo);
    };

    using FramebufferType = std::unique_ptr<Framebuffer>;
} // namespace brasio::renderer::vulkan
