#include <renderer/vulkan/image.hh>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan
{
    Image::Image(const VkDevice &logicalDevice, const VkImage &image,
                 const VkImageViewCreateInfo &createInfo)
        : Handler("image view",
                  [logicalDevice](const VkImageView &imageView) {
                      vkDestroyImageView(logicalDevice, imageView, nullptr);
                  })
        , _image(image)
    {
        io::logging::Logger::trace(std::cout, "Creating image view",
                                   { "CREATE" });
        if (vkCreateImageView(logicalDevice, &createInfo, nullptr, &getHandle())
            != VK_SUCCESS)
        {
            io::logging::Logger::critical(
                std::cout, "Could not create image view", { "CREATE" });
        }
        io::logging::Logger::trace(std::cout, "Created image view",
                                   { "CREATE" });
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
        return getHandle();
    }

    VkImageView &Image::getImageView()
    {
        return getHandle();
    }
} // namespace brasio::renderer::vulkan
