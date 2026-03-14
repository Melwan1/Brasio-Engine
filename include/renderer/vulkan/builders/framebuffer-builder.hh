#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/logical-device.hh>

namespace brasio::renderer::vulkan::builders
{
    class FramebufferBuilder : public core::Builder<VkFramebuffer>
    {
    public:
        FramebufferBuilder(const VkDevice &logicalDevice,
                           const VkRenderPass &renderPass,
                           const VkExtent2D &extent);

        virtual FramebufferBuilder &base() override;

        FramebufferBuilder &
        withAdditionalAttachment(const VkImageView &imageView);

        virtual VkFramebuffer build() override;

    private:
        VkDevice _logicalDevice;
        VkRenderPass _renderPass = VK_NULL_HANDLE;
        VkExtent2D _extent;

        VkStructureType _structureType;
        std::vector<VkImageView> _attachments = {};
        uint32_t _layers;
    };
} // namespace brasio::renderer::vulkan::builders
