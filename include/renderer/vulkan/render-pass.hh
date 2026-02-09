#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/logical-device.hh>

class RenderPass
{
public:
    RenderPass(const VkDevice &logicalDevice,
               const VkRenderPassCreateInfo &createInfo);
    ~RenderPass();

    const VkRenderPass &getHandle() const;
    VkRenderPass &getHandle();

private:
    VkDevice _logicalDevice;
    VkRenderPass _renderPass = VK_NULL_HANDLE;
};

using RenderPassType = std::unique_ptr<RenderPass>;
