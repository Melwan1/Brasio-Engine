#pragma once

#include <core/handler.hh>

#include <memory>

#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class RenderPass : public core::Handler<VkRenderPass>
    {
    public:
        RenderPass(const VulkanRenderer &renderer, const VkRenderPassCreateInfo &createInfo);

    private:
    };

    using RenderPassType = std::unique_ptr<RenderPass>;
} // namespace brasio::renderer::vulkan
