#include <renderer/vulkan/command-buffer.hh>
#include <renderer/vulkan/image-attachment.hh>
#include <renderer/vulkan/builders/buffer-builder.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan
{

    ImageAttachment::ImageAttachment(const LogicalDeviceType &logicalDevice, const VkImageCreateInfo &imageCreateInfo, VkImageViewCreateInfo imageViewCreateInfo)
        : PairHandler("image view", "image", 
                [&logicalDevice](const VkImageView &imageView) { vkDestroyImageView(logicalDevice->getHandle(), imageView, nullptr); },
                [&logicalDevice](const VkImage &image) { vkDestroyImage(logicalDevice->getHandle(), image, nullptr); })
        , _logicalDevice(logicalDevice)
        , _deviceMemory(nullptr)
        , _format(imageCreateInfo.format)
        , _imageViewCreateInfo(imageViewCreateInfo)
        , _width(imageCreateInfo.extent.width)
        , _height(imageCreateInfo.extent.height)
    {
        createImage(imageCreateInfo);
        _imageViewCreateInfo.image = getImage();
    }

    ImageAttachment::ImageAttachment(const LogicalDeviceType &logicalDevice, const VkImage &image, const VkImageViewCreateInfo &imageViewCreateInfo)
        : PairHandler(VK_NULL_HANDLE, image, "image view", "image",
                [&logicalDevice](const VkImageView &imageView) { vkDestroyImageView(logicalDevice->getHandle(), imageView, nullptr); },
                [](const VkImage &) { BRASIO_LOG_TRACE("Nothing to be done to destroy image", { "DESTROY" }); })
        , _logicalDevice(logicalDevice)
        , _deviceMemory(nullptr)
        , _format(imageViewCreateInfo.format)
        , _width(0)
        , _height(0)
    {
        createImageView(imageViewCreateInfo);
    }

    VkImage &ImageAttachment::getImage()
    {
        return getHandle2();
    }

    const VkImage &ImageAttachment::getImage() const
    {
        return getHandle2();
    }

    VkImageView &ImageAttachment::getImageView()
    {
        return getHandle1();
    }

    const VkImageView &ImageAttachment::getImageView() const
    {
        return getHandle1();
    }

    void ImageAttachment::createImage(const VkImageCreateInfo &imageCreateInfo)
    {
        BRASIO_LOG_TRACE("Creating image", { "CREATE" });

        if (vkCreateImage(_logicalDevice->getHandle(), &imageCreateInfo, nullptr, &getImage()) != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL("Could not create image", { "CREATE" });
        }
        BRASIO_LOG_TRACE("Created image", { "CREATE" });
    }

    void ImageAttachment::createImageView()
    {
        createImageView(_imageViewCreateInfo);
    }

    void ImageAttachment::createImageView(VkImageViewCreateInfo imageViewCreateInfo)
    {
        BRASIO_LOG_TRACE("Creating image view", { "CREATE" });

        if (vkCreateImageView(_logicalDevice->getHandle(), &imageViewCreateInfo, nullptr, &getImageView()) != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL("Could not create image view", { "CREATE" });
        }
        BRASIO_LOG_TRACE("Created image view", { "CREATE" });
    }

    void ImageAttachment::transitionImageLayout(const VkCommandPool &commandPool,
                                        [[maybe_unused]] const VkFormat &format,
                                        const VkImageLayout &oldLayout,
                                        const VkImageLayout &newLayout)
    {
        CommandBuffer commandBuffer(_logicalDevice, commandPool);

        VkPipelineStageFlags sourceStage = VK_PIPELINE_STAGE_NONE;
        VkPipelineStageFlags destinationStage = VK_PIPELINE_STAGE_NONE;

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = oldLayout;
        barrier.newLayout = newLayout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = getImage();
        barrier.subresourceRange = { .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                     .baseMipLevel = 0,
                                     .levelCount = 1,
                                     .baseArrayLayer = 0,
                                     .layerCount = 1 };
        if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
        {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        }
        else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
            sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        }
        else {
            BRASIO_LOG_ERROR("Unsupported layout transition", { "CREATE", "TEXTURE" });
        }

        vkCmdPipelineBarrier(commandBuffer.getHandle(), sourceStage, destinationStage, 0, 0, nullptr, 0,
                             nullptr, 1, &barrier);
    }

    void ImageAttachment::initMemory(const PhysicalDeviceType &physicalDevice, const VkCommandPool &commandPool, size_t size, void *data, const VkMemoryPropertyFlags &memoryProperties)
    {
        initMemory(physicalDevice, memoryProperties);
        builders::BufferBuilder stagingBuilder(physicalDevice, _logicalDevice);
        BufferType stagingBuffer = stagingBuilder.withSize(size).withData(data).withUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT).withMemoryProperties(memoryProperties).build();

        transitionImageLayout(commandPool, _format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        stagingBuffer->copyInto(*this, commandPool);
        transitionImageLayout(commandPool, _format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    }

    void ImageAttachment::initMemory(const PhysicalDeviceType &physicalDevice, const VkMemoryPropertyFlags &memoryProperties)
    {
        _deviceMemory = std::make_unique<Memory>(physicalDevice, _logicalDevice->getHandle(), *this, memoryProperties);
    }

    size_t ImageAttachment::getWidth() const
    {
        return _width;
    }

    size_t ImageAttachment::getHeight() const
    {
        return _height;
    }

    size_t ImageAttachment::getSize() const
    {
        return _width * _height;
    }

    VkAttachmentDescription ImageAttachment::getAttachmentDescription() const 
    {
        return sGetAttachmentDescription(_format);
    }

    VkAttachmentReference ImageAttachment::getAttachmentReference(uint32_t attachmentId) const
    {
        return sGetAttachmentReference(attachmentId);
    }

    VkAttachmentDescription ImageAttachment::sGetAttachmentDescription(const VkFormat &format)
    {
        VkAttachmentDescription attachmentDescription{};
        attachmentDescription.format = format;
        attachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
        attachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        attachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        attachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        
        return attachmentDescription;
    }

    VkAttachmentReference ImageAttachment::sGetAttachmentReference(uint32_t attachmentId)
    {
        VkAttachmentReference attachmentReference{};
        attachmentReference.attachment = attachmentId;
        attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        return attachmentReference;
    }

}
