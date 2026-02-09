#include <renderer/vulkan/image.hh>

#include <io/logging/logger.hh>

Image::Image(const VkDevice &logicalDevice, const VkImage &image,
             const VkImageViewCreateInfo &createInfo)
    : _logicalDevice(logicalDevice)
    , _image(image)
{
    Logger::trace(std::cout, "Creating image view", { "CREATE" });
    if (vkCreateImageView(_logicalDevice, &createInfo, nullptr, &_imageView)
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create image view",
                         { "CREATE" });
    }
    Logger::trace(std::cout, "Created image view", { "CREATE" });
}

Image::~Image()
{
    Logger::trace(std::cout, "Destroying image view", { "CREATE" });
    vkDestroyImageView(_logicalDevice, _imageView, nullptr);
    Logger::trace(std::cout, "Destroyed image view", { "CREATE" });
}

const VkImage &Image::getImage() const
{
    return _image;
}

VkImage &Image::getImage()
{
    return _image;
}

const VkImageView &Image::getImageView() const
{
    return _imageView;
}

VkImageView &Image::getImageView()
{
    return _imageView;
}
