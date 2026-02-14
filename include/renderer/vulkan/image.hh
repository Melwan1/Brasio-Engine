#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/logical-device.hh>

#include <core/handler.hh>

class Image : public Handler<VkImageView>
{
public:
    Image(const VkDevice &logicalDevice, const VkImage &image,
          const VkImageViewCreateInfo &createInfo);

    const VkImage &getImage() const;
    VkImage &getImage();

    const VkImageView &getImageView() const;
    VkImageView &getImageView();

private:
    VkImage _image;
};

using ImageType = std::unique_ptr<Image>;
