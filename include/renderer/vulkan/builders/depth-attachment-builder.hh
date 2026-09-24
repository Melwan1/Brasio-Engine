#pragma once

#include <core/builder.hh>

#include <renderer/vulkan/depth-attachment.hh>

namespace brasio::renderer::vulkan::builders
{

    class DepthAttachmentBuilder : public core::Builder<DepthAttachmentType>
    {
    public:
        DepthAttachmentBuilder(const PhysicalDeviceType &physicalDevice,
                               const LogicalDeviceType &logicalDevice);

        virtual DepthAttachmentBuilder &base() override;
        virtual DepthAttachmentType build() override;

        DepthAttachmentBuilder &withWidth(uint32_t width);
        DepthAttachmentBuilder &withHeight(uint32_t height);
        DepthAttachmentBuilder &withExtent(uint32_t width, uint32_t height);
        DepthAttachmentBuilder &withFormat(const VkFormat &format);

    private:
        const PhysicalDeviceType &_physicalDevice;
        const LogicalDeviceType &_logicalDevice;

        uint32_t _width;
        uint32_t _height;
        VkFormat _format;
    };
} // namespace brasio::renderer::vulkan::builders
