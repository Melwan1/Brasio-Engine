#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{

    class AttachmentReferenceBuilder : core::Builder<VkAttachmentReference>
    {
    public:
        AttachmentReferenceBuilder();
        virtual AttachmentReferenceBuilder &base() override;
        virtual VkAttachmentReference build() override;

    private:
        uint32_t _index;
        VkImageLayout _layout;
    };
} // namespace brasio::renderer::vulkan::builders
