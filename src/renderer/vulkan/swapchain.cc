#include <renderer/vulkan/swapchain.hh>

#include <io/logging/logger.hh>
#include <renderer/vulkan/builders/image-builder.hh>
#include <renderer/vulkan/builders/framebuffer-builder.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    Swapchain::Swapchain(const LogicalDeviceType &logicalDevice,
                         const VkSwapchainCreateInfoKHR &createInfo)
        : Handler("swapchain",
                  [&logicalDevice](const VkSwapchainKHR &swapchain) {
                      vkDestroySwapchainKHR(logicalDevice->getHandle(), swapchain, nullptr);
                  })
        , _logicalDevice(logicalDevice)
    {
        BRASIO_LOG_TRACE("Creating swapchain", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreateSwapchainKHR(_logicalDevice->getHandle(), &createInfo, nullptr, &getHandle()),
            "create swapchain", { "CREATE" });
        BRASIO_LOG_TRACE("Created swapchain", { "CREATE" });
        BRASIO_LOG_TRACE("Setting image format, extent and image count", { "CREATE" });
        _format = createInfo.imageFormat;
        _extent = createInfo.imageExtent;
        _presentMode = createInfo.presentMode;
        _imageCount = createInfo.minImageCount;
        BRASIO_LOG_TRACE("Set image format, extent and image count", { "CREATE" });
        _images.clear();
        _framebuffers.clear();
        createImages();
    }

    const VkFormat &Swapchain::getFormat() const
    {
        return _format;
    }

    VkFormat &Swapchain::getFormat()
    {
        return _format;
    }

    const VkExtent2D &Swapchain::getExtent() const
    {
        return _extent;
    }

    VkExtent2D &Swapchain::getExtent()
    {
        return _extent;
    }

    uint32_t Swapchain::getImageCount() const
    {
        return _imageCount;
    }

    VkPresentModeKHR Swapchain::getPresentMode() const
    {
        return _presentMode;
    }

    const Image &Swapchain::imageAt(uint32_t index) const
    {
        return *_images.at(index);
    }

    Image &Swapchain::imageAt(uint32_t index)
    {
        return *_images.at(index);
    }

    const VkFramebuffer &Swapchain::framebufferAt(uint32_t index) const
    {
        return _framebuffers.at(index)->getHandle();
    }

    VkFramebuffer &Swapchain::framebufferAt(uint32_t index)
    {
        return _framebuffers.at(index)->getHandle();
    }

    void Swapchain::createImages()
    {
        std::vector<VkImage> rawImages;
        BRASIO_LOG_TRACE("Getting swapchain images", { "CREATE" });
        vkGetSwapchainImagesKHR(_logicalDevice->getHandle(), getHandle(), &_imageCount, nullptr);
        BRASIO_LOG_TRACE("Getting " + std::to_string(_imageCount) + " swapchain images",
                         { "CREATE" });

        rawImages.resize(_imageCount);
        vkGetSwapchainImagesKHR(_logicalDevice->getHandle(), getHandle(), &_imageCount,
                                rawImages.data());
        for (const auto &image : rawImages)
        {
            _images.emplace_back(
                builders::ImageBuilder(_logicalDevice, image, getFormat()).build());
        }
        BRASIO_LOG_TRACE("Got swapchain images", { "CREATE" });
    }

    void Swapchain::createFramebuffers(const VkRenderPass &renderPass,
                                       const std::vector<VkImageView> &additionalImageViews)
    {
        for (const auto &image : _images)
        {
            builders::FramebufferBuilder builder(_logicalDevice, renderPass, getExtent());
            for (const VkImageView &imageView : additionalImageViews)
            {
                builder.withAdditionalAttachment(imageView);
            }
            builder.withAdditionalAttachment(image->getImageView());
            _framebuffers.emplace_back(builder.build());
        }
    }

    float Swapchain::getWidth() const
    {
        return getExtent().width;
    }

    float Swapchain::getHeight() const
    {
        return getExtent().height;
    }

    Swapchain::~Swapchain()
    {
        _framebuffers.clear();
        _images.clear();
    }
} // namespace brasio::renderer::vulkan
