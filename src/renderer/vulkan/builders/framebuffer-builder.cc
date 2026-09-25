#include <renderer/vulkan/builders/framebuffer-builder.hh>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan::builders
{
    FramebufferBuilder::FramebufferBuilder(const LogicalDeviceType &logicalDevice,
                                           const VkRenderPass &renderPass, const VkExtent2D &extent)
        : _logicalDevice(logicalDevice)
        , _renderPass(renderPass)
        , _extent(extent)
    {
        base();
    }

    FramebufferBuilder &FramebufferBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        _attachments.clear();
        _layers = 1;

        return *this;
    }

    FramebufferBuilder &FramebufferBuilder::withAdditionalAttachment(const VkImageView &imageView)
    {
        _attachments.emplace_back(imageView);
        return *this;
    }

    FramebufferType FramebufferBuilder::build()
    {
        VkFramebufferCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.renderPass = _renderPass;
        createInfo.attachmentCount = _attachments.size();
        createInfo.pAttachments = _attachments.data();
        createInfo.width = _extent.width;
        createInfo.height = _extent.height;
        createInfo.layers = _layers;

        return std::make_unique<Framebuffer>(_logicalDevice, createInfo);
    }
} // namespace brasio::renderer::vulkan::builders
