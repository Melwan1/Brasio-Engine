#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{

    class AttachmentDescriptionBuilder
        : public core::Builder<VkAttachmentDescription>
    {
    public:
        AttachmentDescriptionBuilder(const VkFormat &format);

        virtual AttachmentDescriptionBuilder &base() override;
        virtual VkAttachmentDescription build() override;

    private:
        VkFormat _format;
        VkSampleCountFlagBits _samples;
        VkAttachmentLoadOp _loadOp;
        VkAttachmentStoreOp _storeOp;
        VkAttachmentLoadOp _stencilLoadOp;
        VkAttachmentStoreOp _stencilStoreOp;
        VkImageLayout _initialLayout;
        VkImageLayout _finalLayout;
    };
} // namespace brasio::renderer::vulkan::builders
