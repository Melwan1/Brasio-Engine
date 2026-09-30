#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/framebuffer.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;
}

namespace brasio::renderer::vulkan::builders
{
    class FramebufferBuilder : public core::Builder<FramebufferType>
    {
    public:
        FramebufferBuilder(const VulkanRenderer &renderer);

        virtual FramebufferBuilder &base() override;

        FramebufferBuilder &withAdditionalAttachment(const VkImageView &imageView);

        virtual FramebufferType build() override;

    private:
        const VulkanRenderer &_renderer;
        VkStructureType _structureType;
        std::vector<VkImageView> _attachments = {};
        uint32_t _layers;
    };
} // namespace brasio::renderer::vulkan::builders
