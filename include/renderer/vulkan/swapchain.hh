#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/image.hh>
#include <renderer/vulkan/framebuffer.hh>

namespace brasio::renderer::vulkan
{
    class Swapchain : public core::Handler<VkSwapchainKHR>
    {
    public:
        Swapchain(const LogicalDeviceType &logicalDevice,
                  const VkSwapchainCreateInfoKHR &createInfo);
        ~Swapchain();

        const VkFormat &getFormat() const;
        VkFormat &getFormat();

        const VkExtent2D &getExtent() const;
        VkExtent2D &getExtent();

        uint32_t getImageCount() const;

        VkPresentModeKHR getPresentMode() const;

        const Image &imageAt(uint32_t index) const;
        Image &imageAt(uint32_t index);

        const VkFramebuffer &framebufferAt(uint32_t index) const;
        VkFramebuffer &framebufferAt(uint32_t index);

        void createImages();
        void createFramebuffers(const VkRenderPass &renderPass,
                                const std::vector<VkImageView> &additionalImageViews);

        float getWidth() const;
        float getHeight() const;

    private:
        const LogicalDeviceType &_logicalDevice;
        VkFormat _format;
        VkExtent2D _extent;
        VkPresentModeKHR _presentMode;
        uint32_t _imageCount;
        std::vector<ImageType> _images;
        std::vector<FramebufferType> _framebuffers;
    };

    using SwapchainType = std::unique_ptr<Swapchain>;
} // namespace brasio::renderer::vulkan
