#include <renderer/vulkan/builders/swapchain-builder.hh>

#include <algorithm>
#include <limits>

#include <renderer/vulkan/swap-chain-support-details.hh>

#include <io/logging/logger.hh>

SwapchainBuilder::SwapchainBuilder(GLFWwindow *window,
                                   const PhysicalDevice &physicalDevice,
                                   const VkDevice &logicalDevice,
                                   const VkSurfaceKHR &surface)
    : _window(window)
    , _physicalDevice(physicalDevice)
    , _logicalDevice(logicalDevice)
    , _surface(surface)
{
    base();
}

SwapchainBuilder &SwapchainBuilder::base()
{
    SwapChainSupportDetails swapchainSupportDetails =
        _physicalDevice.querySwapChainSupport();
    std::ostringstream oss;

    _availableSurfaceFormats = swapchainSupportDetails.formats;
    oss << "Available surface formats: " << _availableSurfaceFormats.size();
    Logger::info(std::cout, oss.str(), { "CREATE" });
    oss = std::ostringstream();

    _availablePresentModes = swapchainSupportDetails.presentModes;
    oss << "Available present modes: " << _availablePresentModes.size();
    Logger::info(std::cout, oss.str(), { "CREATE" });
    oss = std::ostringstream();

    _availableCapabilities = swapchainSupportDetails.capabilities;
    oss << "Available capabilities: "
        << _availableCapabilities.currentExtent.width << " x "
        << _availableCapabilities.currentExtent.height;
    Logger::info(std::cout, oss.str(), { "CREATE" });
    oss = std::ostringstream();

    _surfaceFormat = _availableSurfaceFormats[0];
    _presentMode = VK_PRESENT_MODE_FIFO_KHR;
    _extent = _getExtent(_availableCapabilities);

    _imageCount = swapchainSupportDetails.capabilities.minImageCount + 1;
    oss << "Setting swapchain image count to " << _imageCount;
    Logger::info(std::cout, oss.str(), { "CREATE" });
    oss = std::ostringstream();
    if (swapchainSupportDetails.capabilities.maxImageCount > 0
        && _imageCount > swapchainSupportDetails.capabilities.maxImageCount)
    {
        _imageCount = swapchainSupportDetails.capabilities.maxImageCount;
        oss << "Swapchain image count was too large, reducing to "
            << _imageCount;
        Logger::warning(std::cout, oss.str(), { "CREATE " });
    }
    return *this;
}

SwapchainType SwapchainBuilder::build()
{
    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = _surface;
    createInfo.minImageCount = _imageCount;
    createInfo.imageFormat = _surfaceFormat.format;
    createInfo.imageColorSpace = _surfaceFormat.colorSpace;
    createInfo.imageExtent = _extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = _physicalDevice.findQueueFamilies();
    uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(),
                                      indices.presentFamily.value() };
    bool areIndicesSame =
        indices.graphicsFamily.value() == indices.presentFamily.value();

    createInfo.imageSharingMode =
        areIndicesSame ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount = areIndicesSame ? 0 : 2;
    createInfo.pQueueFamilyIndices =
        areIndicesSame ? nullptr : queueFamilyIndices;
    createInfo.preTransform =
        _physicalDevice.querySwapChainSupport().capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = _presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    return std::make_unique<Swapchain>(_logicalDevice, createInfo);
}

SwapchainBuilder &
SwapchainBuilder::withSurfaceFormat(const VkSurfaceFormatKHR &surfaceFormat)
{
    Logger::trace(std::cout, "Searching for surface format", { "CREATE" });
    if (std::find_if(_availableSurfaceFormats.begin(),
                     _availableSurfaceFormats.end(),
                     [&surfaceFormat](auto &other) {
                         return other.format == surfaceFormat.format
                             && other.colorSpace == surfaceFormat.colorSpace;
                     })
        != _availableSurfaceFormats.end())
    {
        Logger::trace(std::cout, "Surface format found", { "CREATE" });
        _surfaceFormat = surfaceFormat;
    }
    else
    {
        Logger::warning(std::cout,
                        "Surface format not found, defaulting to the previous "
                        "selected format",
                        { "CREATE" });
    }
    return *this;
}

SwapchainBuilder &
SwapchainBuilder::withPresentMode(const VkPresentModeKHR &presentMode)
{
    Logger::trace(std::cout, "Searching for present mode", { "CREATE" });
    if (std::find(_availablePresentModes.begin(), _availablePresentModes.end(),
                  presentMode)
        != _availablePresentModes.end())
    {
        Logger::trace(std::cout, "Present mode found", { "CREATE" });
        _presentMode = presentMode;
    }
    else
    {
        Logger::warning(
            std::cout,
            "Present mode not found, defaulting to the previous selected mode",
            { "CREATE" });
    }
    return *this;
}

VkExtent2D
SwapchainBuilder::_getExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
    Logger::trace(std::cout, "Searching for extent", { "CREATE" });
    if (capabilities.currentExtent.width
        != std::numeric_limits<uint32_t>::max())
    {
        Logger::trace(std::cout, "Extent found in swapchain support details",
                      { "CREATE" });
        return capabilities.currentExtent;
    }
    Logger::trace(std::cout,
                  "Extent not found in swapchain support details, "
                  "extracting from GLFW framebuffer",
                  { "CREATE" });
    VkExtent2D extent;
    int width;
    int height;
    glfwGetFramebufferSize(_window, &width, &height);

    uint32_t extentWidth = static_cast<uint32_t>(width);
    uint32_t extentHeight = static_cast<uint32_t>(height);
    width = std::clamp(extentWidth, capabilities.minImageExtent.width,
                       capabilities.maxImageExtent.width);
    height = std::clamp(extentHeight, capabilities.minImageExtent.height,
                        capabilities.maxImageExtent.height);

    extent = { extentWidth, extentHeight };
    return extent;
}
