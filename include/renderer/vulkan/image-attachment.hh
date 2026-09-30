#pragma once

#include <core/pair-handler.hh>

#include <vulkan/vulkan_core.h>
#include <renderer/vulkan/command-buffer.hh>
#include <renderer/vulkan/memory.hh>

namespace brasio::renderer::vulkan
{

    class ImageAttachment : public core::PairHandler<VkImageView, VkImage>
    {
    public:
        ImageAttachment(const VulkanRenderer &renderer, VkImageCreateInfo imageCreateInfo,
                        VkImageViewCreateInfo imageViewCreateInfo);
        ImageAttachment(const VulkanRenderer &renderer, const VkImage &image,
                        const VkImageViewCreateInfo &imageViewCreateInfo);

        VkImage &getImage();
        const VkImage &getImage() const;
        VkImageView &getImageView();
        const VkImageView &getImageView() const;

        void createImage(const VkImageCreateInfo &imageCreateInfo);
        void createImageView();
        void createImageView(VkImageViewCreateInfo imageViewCreateInfo);

        void transitionImageLayout([[maybe_unused]] const VkFormat &format,
                                   const VkImageLayout &oldLayout, const VkImageLayout &newLayout);
        void barrierTransfer(const CommandBuffer &commandBuffer, VkPipelineStageFlags sourceStage,
                             VkPipelineStageFlags destinationStage, VkImageLayout oldLayout,
                             VkImageLayout newLayout, VkAccessFlags srcAccess,
                             VkAccessFlags dstAccess, uint32_t mipLevel = 0,
                             uint32_t mipLevelCount = 1);
        void barrierTransfer(const CommandBuffer &commandBuffer, VkPipelineStageFlags stage,
                             VkImageLayout oldLayout, VkImageLayout newLayout,
                             VkAccessFlags srcAccess, VkAccessFlags dstAccess,
                             uint32_t mipLevel = 0, uint32_t mipLevelCount = 1);
        std::pair<int32_t, int32_t> blitToNextMipLevel(const CommandBuffer &commandBuffer,
                                                       uint32_t mipLevel, int32_t mipWidth,
                                                       int32_t mipHeight);
        void generateMipmaps();

        void initMemory(size_t size, void *data);
        void initMemory();

        size_t getWidth() const;
        size_t getHeight() const;
        size_t getSize() const;
        uint32_t getMipLevels() const;

        virtual VkAttachmentDescription getAttachmentDescription() const;
        virtual VkAttachmentReference getAttachmentReference(uint32_t attachmentId) const;

        static VkAttachmentDescription sGetAttachmentDescription(const VkFormat &format);
        static VkAttachmentReference sGetAttachmentReference(uint32_t attachmentId);

    protected:
        const VulkanRenderer &_renderer;

    private:
        MemoryType _deviceMemory;
        VkFormat _format;
        VkImageViewCreateInfo _imageViewCreateInfo{};
        size_t _width;
        size_t _height;
        VkSampleCountFlagBits _sampleCount;
    };

    using ImageAttachmentType = std::unique_ptr<ImageAttachment>;

} // namespace brasio::renderer::vulkan
