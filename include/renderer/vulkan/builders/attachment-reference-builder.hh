#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

class AttachmentReferenceBuilder : Builder<VkAttachmentReference>
{
public:
    AttachmentReferenceBuilder();
    virtual AttachmentReferenceBuilder &base() override;
    virtual VkAttachmentReference build() override;

private:
    uint32_t _index;
    VkImageLayout _layout;
};
