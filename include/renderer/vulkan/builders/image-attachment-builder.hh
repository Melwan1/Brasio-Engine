#pragma once

#include <core/builder.hh>
#include <renderer/vulkan/image-attachment.hh>

namespace brasio::renderer::vulkan::builders
{
    class ImageAttachmentBuilder : public core::Builder<ImageAttachmentType>
    {
    public:
        ImageAttachmentBuilder(const VulkanRenderer &renderer);

        virtual ImageAttachmentBuilder &base() override;
        virtual ImageAttachmentType build() override;

        ImageAttachmentBuilder &withWidth(uint32_t width);
        ImageAttachmentBuilder &withHeight(uint32_t height);
        ImageAttachmentBuilder &withExtent(uint32_t width, uint32_t height);
        ImageAttachmentBuilder &withImageType(const VkImageType &imageType);
        ImageAttachmentBuilder &withFormat(const VkFormat &format);
        ImageAttachmentBuilder &withUsage(const VkImageUsageFlags &usage);
        ImageAttachmentBuilder &withSharingMode(const VkSharingMode &sharingMode);
        ImageAttachmentBuilder &withTiling(const VkImageTiling &tiling);
        ImageAttachmentBuilder &withSamples(const VkSampleCountFlagBits &sampleCount);

    private:
        const VulkanRenderer &_renderer;

        uint32_t _width;
        uint32_t _height;
        VkImageType _imageType;
        VkFormat _format;
        VkImageUsageFlags _usage;
        VkSharingMode _sharingMode;
        VkImageTiling _tiling;
        VkSampleCountFlagBits _sampleCount;
    };
} // namespace brasio::renderer::vulkan::builders
