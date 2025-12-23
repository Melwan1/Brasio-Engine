#pragma once

#include <renderer/renderer.hh>

#include <ostream>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

#include <renderer/queue-family-indices.hh>

/**
 * The Vulkan Renderer.
 *
 * Uses Vulkan as the base API to renderer objects to the window.
 */

class VulkanRenderer : public Renderer
{
public:
    VulkanRenderer(GLFWwindow *window);

    ~VulkanRenderer();

    virtual void init() override;

    void printExtensions(std::ostream &ostr);
    VkApplicationInfo getApplicationInfo();
    void createInstance();
    bool checkValidationLayerSupport();
    std::vector<const char *> getExtensions();

    VkDebugUtilsMessengerCreateInfoEXT getDebugUtilsMessengerCreateInfo();
    void setupDebugMessenger();

    void createSurface();

    void pickPhysicalDevice();
    QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &device);

    void createLogicalDevice();
    void getDeviceQueues(const QueueFamilyIndices &indices);

private:
    GLFWwindow *_window;
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

    VkSurfaceKHR _surface = VK_NULL_HANDLE;

    VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;

    std::vector<VkPhysicalDevice> getAvailablePhysicalDevices();
    bool isDeviceSuitable(const VkPhysicalDevice &device);
    int getDeviceSuitability(const VkPhysicalDevice &device);

    VkDevice _device = VK_NULL_HANDLE;
    VkQueue _graphicsQueue = VK_NULL_HANDLE;
    VkQueue _presentationQueue = VK_NULL_HANDLE;
};
