#include <renderer/vulkan-renderer.hh>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include <iostream>
#include <map>
#include <set>

#include <io/debug/vulkan-renderer-debug-printer.hh>

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *callbackData, void *userData)
{
    (void)userData;
    VulkanRendererDebugPrinter::printDebugMessage(std::cout, messageSeverity,
                                                  messageType, callbackData);
    return VK_FALSE;
}

VulkanRenderer::VulkanRenderer(GLFWwindow *window)
{
    _window = window;
    createInstance();
    setupDebugMessenger();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
}

void VulkanRenderer::init()
{}

VulkanRenderer::~VulkanRenderer()
{
    if (_enableValidationLayers)
    {
        destroyDebugUtilsMessengerEXT(_instance, _debugMessenger, nullptr);
    }
    vkDestroySurfaceKHR(_instance, _surface, nullptr);
    vkDestroyDevice(_device, nullptr);
    vkDestroyInstance(_instance, nullptr);
}

void VulkanRenderer::printExtensions(std::ostream &ostr)
{
    ostr << "Available Vulkan Instance Extensions: ";
    for (auto &extension : _extensions)
    {
        ostr << extension.extensionName << ", ";
    }
    ostr << std::endl;
}

VkApplicationInfo VulkanRenderer::getApplicationInfo()
{
    VkApplicationInfo applicationInfo{};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = "Brasio Engine";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    applicationInfo.pEngineName = "Brasio Engine";
    applicationInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    applicationInfo.apiVersion = VK_API_VERSION_1_3;
    applicationInfo.pNext = nullptr;
    return applicationInfo;
}

void VulkanRenderer::createInstance()
{
    VkInstanceCreateInfo createInfo{};

    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    VkApplicationInfo applicationInfo = getApplicationInfo();
    createInfo.pApplicationInfo = &applicationInfo;

    std::vector<const char *> extensions = getExtensions();

    createInfo.enabledExtensionCount = extensions.size();
    createInfo.ppEnabledExtensionNames = extensions.data();

    vkEnumerateInstanceExtensionProperties(nullptr, &_extensionCount, nullptr);
    _extensions.resize(_extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &_extensionCount,
                                           _extensions.data());

    printExtensions(std::cout);
    VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo{};

    if (_enableValidationLayers && !checkValidationLayerSupport())
    {
        throw std::runtime_error("Validation layers requested but not found.");
    }

    if (_enableValidationLayers)
    {
        createInfo.enabledLayerCount = _validationLayers.size();
        createInfo.ppEnabledLayerNames = _validationLayers.data();
        debugMessengerCreateInfo = getDebugUtilsMessengerCreateInfo();
        createInfo.pNext = &debugMessengerCreateInfo;
    }
    else
    {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create an instance.");
    }
}

bool VulkanRenderer::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    _validationLayers.clear();
    _validationLayers.emplace_back("VK_LAYER_KHRONOS_validation");

    for (auto &layerName : _validationLayers)
    {
        if (std::find_if(availableLayers.begin(), availableLayers.end(),
                         [&layerName](VkLayerProperties &prop) {
                             return !std::strcmp(prop.layerName, layerName);
                         })
            == availableLayers.end())
        {
            return false;
        }
    }
    return true;
}

std::vector<const char *> VulkanRenderer::getExtensions()
{
    uint32_t extensionCount = 0;
    const char **glfwExtensions =
        glfwGetRequiredInstanceExtensions(&extensionCount);
    std::vector<const char *> extensions(glfwExtensions,
                                         glfwExtensions + extensionCount);
    if (_enableValidationLayers)
    {
        extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    return extensions;
}

VkDebugUtilsMessengerCreateInfoEXT
VulkanRenderer::getDebugUtilsMessengerCreateInfo()
{
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = nullptr;
    createInfo.pNext = nullptr;
    return createInfo;
}

VkResult VulkanRenderer::createDebugUtilsMessengerEXT(
    VkInstance &instance, const VkDebugUtilsMessengerCreateInfoEXT &createInfo,
    const VkAllocationCallbacks *allocator,
    VkDebugUtilsMessengerEXT &debugMessenger)
{
    auto function = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
    if (function != nullptr)
    {
        return function(instance, &createInfo, allocator, &debugMessenger);
    }
    return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void VulkanRenderer::destroyDebugUtilsMessengerEXT(
    VkInstance &instance, VkDebugUtilsMessengerEXT &debugMessenger,
    const VkAllocationCallbacks *allocator)
{
    auto function = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
    if (function != nullptr)
    {
        function(instance, debugMessenger, allocator);
    }
}

void VulkanRenderer::setupDebugMessenger()
{
    if (!_enableValidationLayers)
    {
        return;
    }

    VkDebugUtilsMessengerCreateInfoEXT createInfo =
        getDebugUtilsMessengerCreateInfo();

    if (createDebugUtilsMessengerEXT(_instance, createInfo, nullptr,
                                     _debugMessenger)
        != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to setup debug messenger.");
    }
}

void VulkanRenderer::createSurface()
{
    if (glfwCreateWindowSurface(_instance, _window, nullptr, &_surface) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create a window surface.");
    }
}

std::vector<VkPhysicalDevice> VulkanRenderer::getAvailablePhysicalDevices()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        throw std::runtime_error("Failed to find a GPU with Vulkan support.");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());
    return devices;
}

bool VulkanRenderer::isDeviceSuitable(const VkPhysicalDevice &device)
{
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    if (!deviceFeatures.geometryShader || !deviceFeatures.tessellationShader)
    {
        return false;
    }
    QueueFamilyIndices indices = findQueueFamilies(device);
    if (!indices.isComplete())
    {
        return false;
    }
    return true;
}

int VulkanRenderer::getDeviceSuitability(const VkPhysicalDevice &device)
{
    if (!isDeviceSuitable(device))
    {
        return 0;
    }
    int score = 0;
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
        score += 1000;
    }
    score += deviceProperties.limits.maxImageDimension2D;
    return score;
}

void VulkanRenderer::pickPhysicalDevice()
{
    std::vector<VkPhysicalDevice> devices = getAvailablePhysicalDevices();
    std::multimap<int, VkPhysicalDevice> candidates;

    for (const auto &device : devices)
    {
        int score = getDeviceSuitability(device);
        candidates.insert(std::make_pair(score, device));
    }
    if (candidates.rbegin()->first > 0)
    {
        _physicalDevice = candidates.rbegin()->second;
    }
    else {
        throw std::runtime_error("Failed to find a suitable GPU device.");
    }
}

QueueFamilyIndices VulkanRenderer::findQueueFamilies(const VkPhysicalDevice &device)
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto &queueFamily : queueFamilies)
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, _surface, &presentSupport);
        if (presentSupport)
        {
            indices.presentFamily = i;
        }
        i++;
    }
    return indices;
}

void VulkanRenderer::createLogicalDevice()
{
    QueueFamilyIndices indices = findQueueFamilies(_physicalDevice);
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };
    float queuePriority = 1.0f;
    for (const uint32_t queueFamilyIndex : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.emplace_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = 0;

    if (_enableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
        createInfo.ppEnabledLayerNames = _validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(_physicalDevice, &createInfo, nullptr, &_device) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create a logical device.");
    }
    getDeviceQueues(indices);
}

void VulkanRenderer::getDeviceQueues(const QueueFamilyIndices &indices)
{
    vkGetDeviceQueue(_device, indices.graphicsFamily.value(), 0, &_graphicsQueue);
    vkGetDeviceQueue(_device, indices.presentFamily.value(), 0, &_presentationQueue);
}