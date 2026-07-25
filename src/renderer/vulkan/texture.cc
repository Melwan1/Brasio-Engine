#include <renderer/vulkan/texture.hh>

#include <renderer/vulkan/memory.hh>

namespace brasio::renderer::vulkan
{

    Texture::Texture(const PhysicalDeviceType &physicalDevice,
                     const LogicalDeviceType &logicalDevice,
                     const VkImageCreateInfo &imageInfo,
                     const images::P3PPM &textureImage,
                     const VkMemoryPropertyFlags memoryProperties)
        : Handler("texture",
                  [&logicalDevice](const VkImage &image) {
                      vkDestroyImage(logicalDevice->getHandle(), image,
                                     nullptr);
                  })
        , _logicalDevice(logicalDevice)
        , _textureImage(textureImage)
        , _deviceMemory(nullptr)
    {
        BRASIO_LOG_TRACE(std::cout, "Creating texture", { "CREATE" });
        if (vkCreateImage(logicalDevice->getHandle(), &imageInfo, nullptr,
                          &getHandle())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL(std::cout, "Could not create texture",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE(std::cout, "Created texture", { "CREATE" });
        _deviceMemory =
            std::make_unique<Memory>(physicalDevice, logicalDevice->getHandle(),
                                     *this, memoryProperties);
    }

    const images::P3PPM &Texture::getTextureImage() const
    {
        return _textureImage;
    }

} // namespace brasio::renderer::vulkan
