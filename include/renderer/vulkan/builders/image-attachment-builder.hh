#pragma once

#include <core/builder.hh>
#include <renderer/vulkan/image-attachment.hh>

namespace brasio::renderer::vulkan::builders
{
    class ImageAttachmentBuilder : public core::Builder<ImageAttachmentType>
    {
    public:
        ImageAttachmentBuilder(const PhysicalDeviceType &physicalDevice,
                               const LogicalDeviceType &logicalDevice);

        virtual ImageAttachmentBuilder &base() override;
        virtual ImageAttachmentType build() override;

        ImageAttachmentBuilder &withWidth(uint32_t width);
        ImageAttachmentBuilder &withHeight(uint32_t height);
        ImageAttachmentBuilder &withExtent(uint32_t width, uint32_t height);
        ImageAttachmentBuilder &withImageType(const VkImageType &imageType);
        ImageAttachmentBuilder &withFormat(const VkFormat &format);
        ImageAttachmentBuilder &withUsage(const VkImageUsageFlags &usage);
        ImageAttachmentBuilder &
        withSharingMode(const VkSharingMode &sharingMode);
        ImageAttachmentBuilder &
        withMemoryProperties(const VkMemoryPropertyFlags &memoryProperties);
        ImageAttachmentBuilder &withTiling(const VkImageTiling &tiling);
        ImageAttachmentBuilder &
        withSamples(const VkSampleCountFlagBits &sampleCount);

    private:
        const PhysicalDeviceType &_physicalDevice;
        const LogicalDeviceType &_logicalDevice;

        uint32_t _width;
        uint32_t _height;
        VkImageType _imageType;
        VkFormat _format;
        VkImageUsageFlags _usage;
        VkSharingMode _sharingMode;
        VkMemoryPropertyFlags _memoryProperties;
        VkImageTiling _tiling;
        VkSampleCountFlagBits _sampleCount;
    };
} // namespace brasio::renderer::vulkan::builders
