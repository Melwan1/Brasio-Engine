#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/logical-device.hh>

class RenderPass : public Handler<VkRenderPass>
{
public:
    RenderPass(const VkDevice &logicalDevice,
               const VkRenderPassCreateInfo &createInfo);

private:
};

using RenderPassType = std::unique_ptr<RenderPass>;
