#pragma once

#include <vector>

#include <GLFW/glfw3.h>

#include <core/builder.hh>

#include <renderer/vulkan/physical-device.hh>
#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/swapchain.hh>

class SwapchainBuilder : public Builder<SwapchainType>
{
public:
    SwapchainBuilder(GLFWwindow *window, const PhysicalDevice &physicalDevice,
                     const VkDevice &logicalDevice,
                     const VkSurfaceKHR &surface);

    virtual SwapchainBuilder &base() override;

    SwapchainBuilder &
    withSurfaceFormat(const VkSurfaceFormatKHR &surfaceFormat);
    SwapchainBuilder &withPresentMode(const VkPresentModeKHR &presentMode);

    virtual SwapchainType build() override;

private:
    GLFWwindow *_window;
    PhysicalDevice _physicalDevice;
    VkDevice _logicalDevice;
    VkSurfaceKHR _surface;
    std::vector<VkSurfaceFormatKHR> _availableSurfaceFormats;
    std::vector<VkPresentModeKHR> _availablePresentModes;
    VkSurfaceCapabilitiesKHR _availableCapabilities;

    VkSurfaceFormatKHR _surfaceFormat;
    VkPresentModeKHR _presentMode;
    VkExtent2D _extent;
    uint32_t _imageCount;

    VkExtent2D _getExtent(const VkSurfaceCapabilitiesKHR &capabilities);
};
