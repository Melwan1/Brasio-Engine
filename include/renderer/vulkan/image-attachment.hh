#pragma once

#include <core/pair-handler.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/physical-device.hh>
#include <renderer/vulkan/memory.hh>

namespace brasio::renderer::vulkan
{

    class ImageAttachment : public core::PairHandler<VkImageView, VkImage>
    {

        public:

            ImageAttachment(const LogicalDeviceType &logicalDevice, VkImageCreateInfo imageCreateInfo, VkImageViewCreateInfo imageViewCreateInfo);
            ImageAttachment(const LogicalDeviceType &logicalDevice, const VkImage &image, const VkImageViewCreateInfo &imageViewCreateInfo);

            VkImage &getImage();
            const VkImage &getImage() const;
            VkImageView &getImageView();
            const VkImageView &getImageView() const;

            void createImage(const VkImageCreateInfo &imageCreateInfo);
            void createImageView();
            void createImageView(VkImageViewCreateInfo imageViewCreateInfo);

            void transitionImageLayout(const VkCommandPool &commandPool,
                                   [[maybe_unused]] const VkFormat &format,
                                   const VkImageLayout &oldLayout,
                                   const VkImageLayout &newLayout);
            void generateMipmaps(const VkCommandPool &commandPool);

            void initMemory(const PhysicalDeviceType &physicalDevice, const VkCommandPool &commandPool, size_t size, void *data, const VkMemoryPropertyFlags &memoryProperties);
            void initMemory(const PhysicalDeviceType &physicalDevice, const VkMemoryPropertyFlags &memoryProperties);

            size_t getWidth() const;
            size_t getHeight() const;
            size_t getSize() const;
            uint32_t getMipLevels() const;

            virtual VkAttachmentDescription getAttachmentDescription() const;
            virtual VkAttachmentReference getAttachmentReference(uint32_t attachmentId) const;

            static VkAttachmentDescription sGetAttachmentDescription(const VkFormat &format);
            static VkAttachmentReference sGetAttachmentReference(uint32_t attachmentId);

        private:

            const LogicalDeviceType &_logicalDevice;
            MemoryType _deviceMemory;
            VkFormat _format;
            VkImageViewCreateInfo _imageViewCreateInfo{};
            size_t _width;
            size_t _height;

    };

}
