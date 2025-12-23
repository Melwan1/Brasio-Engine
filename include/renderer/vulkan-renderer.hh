#pragma once

#include <renderer/renderer.hh>

#include <ostream>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>

/**
 * The Vulkan Renderer.
 *
 * Uses Vulkan as the base API to renderer objects to the window.
 */

class VulkanRenderer : public Renderer
{
public:
    VulkanRenderer();

    ~VulkanRenderer();

    virtual void init() override;

    void printExtensions(std::ostream &ostr);
    VkApplicationInfo getApplicationInfo();
    void createInstance();
    bool checkValidationLayerSupport();
    std::vector<const char *> getExtensions();

    VkDebugUtilsMessengerCreateInfoEXT getDebugUtilsMessengerCreateInfo();
    void setupDebugMessenger();

    void pickPhysicalDevice();

private:
    VkInstance _instance;
    uint32_t _extensionCount;
    std::vector<VkExtensionProperties> _extensions;

#ifdef NDEBUG
    const bool _enableValidationLayers = false;
#else
    const bool _enableValidationLayers = true;
    std::vector<const char *> _validationLayers;
#endif /* ! NDEBUG */

    VkDebugUtilsMessengerEXT _debugMessenger;

    VkResult createDebugUtilsMessengerEXT(
        VkInstance &instance,
        const VkDebugUtilsMessengerCreateInfoEXT &createInfo,
        const VkAllocationCallbacks *allocator,
        VkDebugUtilsMessengerEXT &debugMessenger);

    void destroyDebugUtilsMessengerEXT(VkInstance &instance,
                                       VkDebugUtilsMessengerEXT &debugMessenger,
                                       const VkAllocationCallbacks *allocator);

    VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;

    std::vector<VkPhysicalDevice> getAvailablePhysicalDevices();

    int getDeviceSuitability(const VkPhysicalDevice &device);
};
