#include <renderer/vulkan/builders/attachment-description-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    AttachmentDescriptionBuilder::AttachmentDescriptionBuilder(
        const VkFormat &format)
        : _format(format)
    {
        base();
    }

    AttachmentDescriptionBuilder &AttachmentDescriptionBuilder::base()
    {
        _samples = VK_SAMPLE_COUNT_1_BIT;
        _loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        _storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        _stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        _stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        _initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        _finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        return *this;
    }

    VkAttachmentDescription AttachmentDescriptionBuilder::build()
    {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = _format;
        colorAttachment.samples = _samples;
        colorAttachment.loadOp = _loadOp;
        colorAttachment.storeOp = _storeOp;
        colorAttachment.stencilLoadOp = _stencilLoadOp;
        colorAttachment.stencilStoreOp = _stencilStoreOp;
        colorAttachment.initialLayout = _initialLayout;
        colorAttachment.finalLayout = _finalLayout;
        return colorAttachment;
    }
} // namespace brasio::renderer::vulkan::builders
