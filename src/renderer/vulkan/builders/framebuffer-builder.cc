#include <renderer/vulkan/builders/framebuffer-builder.hh>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan::builders
{
    FramebufferBuilder::FramebufferBuilder(const VkDevice &logicalDevice,
                                           const VkRenderPass &renderPass,
                                           const VkExtent2D &extent)
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

    FramebufferBuilder &
    FramebufferBuilder::withAdditionalAttachment(const VkImageView &imageView)
    {
        _attachments.emplace_back(imageView);
        return *this;
    }

    VkFramebuffer FramebufferBuilder::build()
    {
        VkFramebufferCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.renderPass = _renderPass;
        createInfo.attachmentCount = _attachments.size();
        createInfo.pAttachments = _attachments.data();
        createInfo.width = _extent.width;
        createInfo.height = _extent.height;
        createInfo.layers = _layers;

        BRASIO_LOG_TRACE(std::cout, "Creating framebuffer", { "CREATE" });

        VkFramebuffer framebuffer;

        if (vkCreateFramebuffer(_logicalDevice, &createInfo, nullptr,
                                &framebuffer)
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL(std::cout, "Could not create framebuffer",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE(std::cout, "Created framebuffer", { "CREATE" });
        return framebuffer;
    }
} // namespace brasio::renderer::vulkan::builders
