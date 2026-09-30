#pragma once

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class TextureSampler : public core::Handler<VkSampler>
    {
    public:
        TextureSampler(const VulkanRenderer &renderer, const VkSamplerCreateInfo &samplerInfo);
    };

    using TextureSamplerType = std::unique_ptr<TextureSampler>;
} // namespace brasio::renderer::vulkan
