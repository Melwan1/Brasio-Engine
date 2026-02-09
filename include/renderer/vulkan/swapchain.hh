#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/image.hh>

class Swapchain
{
public:
    Swapchain(const VkDevice &logicalDevice,
              const VkSwapchainCreateInfoKHR &createInfo);
    ~Swapchain();

    const VkSwapchainKHR &getHandle() const;
    VkSwapchainKHR &getHandle();

    const VkFormat &getFormat() const;
    VkFormat &getFormat();

    const VkExtent2D &getExtent() const;
    VkExtent2D &getExtent();

    uint32_t getImageCount() const;

    const Image &imageAt(uint32_t index) const;
    Image &imageAt(uint32_t index);

    const VkFramebuffer &framebufferAt(uint32_t index) const;
    VkFramebuffer &framebufferAt(uint32_t index);

    void createImages();
    void createFramebuffers(const VkRenderPass &renderPass);

private:
    VkDevice _logicalDevice;
    VkSwapchainKHR _swapchain;
    VkFormat _format;
    VkExtent2D _extent;
    uint32_t _imageCount;
    std::vector<ImageType> _images;
    std::vector<VkFramebuffer> _framebuffers;
};

using SwapchainType = std::unique_ptr<Swapchain>;
