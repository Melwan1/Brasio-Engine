#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/logical-device.hh>

class Image
{
public:
    Image(const VkDevice &logicalDevice, const VkImage &image,
          const VkImageViewCreateInfo &createInfo);
    ~Image();

    const VkImage &getImage() const;
    VkImage &getImage();

    const VkImageView &getImageView() const;
    VkImageView &getImageView();

private:
    VkDevice _logicalDevice = VK_NULL_HANDLE;
    VkImage _image;
    VkImageView _imageView;
};

using ImageType = std::unique_ptr<Image>;
