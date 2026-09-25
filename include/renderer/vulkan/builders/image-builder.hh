#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/image.hh>

namespace brasio::renderer::vulkan::builders
{
    class ImageBuilder : core::Builder<ImageType>
    {
    public:
        ImageBuilder(const LogicalDeviceType &logicalDevice, const VkImage &image,
                     const VkFormat &format);

        virtual ImageBuilder &base() override;
        virtual ImageType build() override;

        ImageBuilder &withAspectMask(VkImageAspectFlags aspectFlags);

    private:
        const LogicalDeviceType &_logicalDevice;
        VkImage _image;
        VkFormat _format;

        VkStructureType _structureType;
        VkImageViewType _imageViewType;
        VkComponentMapping _componentMapping;
        VkImageAspectFlags _aspectMask;
        uint32_t _baseMipLevel;
        uint32_t _levelCount;
        uint32_t _baseArrayLayer;
        uint32_t _layerCount;
    };
} // namespace brasio::renderer::vulkan::builders
