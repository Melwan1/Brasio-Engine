#include <renderer/vulkan/builders/framebuffer-builder.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::renderer::vulkan::builders
{
    FramebufferBuilder::FramebufferBuilder(const VulkanRenderer &renderer)
        : _renderer(renderer)
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
        createInfo.renderPass = _renderer.getRenderPass();
        createInfo.attachmentCount = _attachments.size();
        createInfo.pAttachments = _attachments.data();
        createInfo.width = _renderer.getSwapchain().getWidth();
        createInfo.height = _renderer.getSwapchain().getHeight();
        createInfo.layers = _layers;

        return std::make_unique<Framebuffer>(_renderer, createInfo);
    }
} // namespace brasio::renderer::vulkan::builders
