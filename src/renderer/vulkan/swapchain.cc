#include <renderer/vulkan/swapchain.hh>

#include <io/logging/logger.hh>
#include <renderer/vulkan/builders/image-builder.hh>
#include <renderer/vulkan/builders/framebuffer-builder.hh>

Swapchain::Swapchain(const VkDevice &logicalDevice,
                     const VkSwapchainCreateInfoKHR &createInfo)
    : Handler("swapchain",
              [logicalDevice](const VkSwapchainKHR &swapchain) {
                  vkDestroySwapchainKHR(logicalDevice, swapchain, nullptr);
              })
    , _logicalDevice(logicalDevice)
{
    Logger::trace(std::cout, "Creating swapchain", { "CREATE" });
    if (vkCreateSwapchainKHR(_logicalDevice, &createInfo, nullptr, &getHandle())
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create swapchain", { "CREATE" });
    }
    Logger::trace(std::cout, "Created swapchain", { "CREATE" });
    Logger::trace(std::cout, "Setting image format, extent and image count",
                  { "CREATE" });
    _format = createInfo.imageFormat;
    _extent = createInfo.imageExtent;
    _imageCount = createInfo.minImageCount;
    Logger::trace(std::cout, "Set image format, extent and image count",
                  { "CREATE" });
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
    return _framebuffers.at(index);
}

VkFramebuffer &Swapchain::framebufferAt(uint32_t index)
{
    return _framebuffers.at(index);
}

void Swapchain::createImages()
{
    std::vector<VkImage> rawImages;
    Logger::trace(std::cout, "Getting swapchain images", { "CREATE" });
    vkGetSwapchainImagesKHR(_logicalDevice, getHandle(), &_imageCount, nullptr);
    std::ostringstream oss;
    oss << "Getting " << _imageCount << " swapchain images";
    Logger::trace(std::cout, oss.str(), { "CREATE" });

    rawImages.resize(_imageCount);
    vkGetSwapchainImagesKHR(_logicalDevice, getHandle(), &_imageCount,
                            rawImages.data());
    for (const auto &image : rawImages)
    {
        _images.emplace_back(
            ImageBuilder(_logicalDevice, image, getFormat()).build());
    }
    Logger::trace(std::cout, "Got swapchain images", { "CREATE" });
}

void Swapchain::createFramebuffers(const VkRenderPass &renderPass)
{
    for (const auto &image : _images)
    {
        _framebuffers.emplace_back(
            FramebufferBuilder(_logicalDevice, renderPass, getExtent())
                .withAdditionalAttachment(image->getImageView())
                .build());
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
    for (auto &framebuffer : _framebuffers)
    {
        vkDestroyFramebuffer(_logicalDevice, framebuffer, nullptr);
    }
    _images.clear(); // destroy all images
}
