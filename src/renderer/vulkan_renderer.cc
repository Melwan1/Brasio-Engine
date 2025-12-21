#include <renderer/vulkan_renderer.hh>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include <algorithm>
#include <iostream>
#include <map>

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *callbackData, void *userData)
{
    (void)userData;
    static std::map<VkDebugUtilsMessageSeverityFlagBitsEXT, std::string>
        severityToString = {
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT, "DEBUG" },
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT, "INFO" },
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT, "WARN" },
            { VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT, "ERROR" }
        };
    static std::map<VkDebugUtilsMessageTypeFlagsEXT, std::string>
        messageTypeToString = {
            { VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT, "GENERAL" },
            { VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT, "VALIDATION" },
            { VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT, "PERFORMANCE" }
        };

    std::cerr << "validation layer: [" << severityToString.at(messageSeverity)
              << "][" << messageTypeToString.at(messageType) << "] "
              << callbackData->pMessage;
    std::cerr << std::endl;
    return VK_FALSE;
}

VulkanRenderer::VulkanRenderer()
{
    createInstance();
    setupDebugMessenger();
}

void VulkanRenderer::init()
{}

VulkanRenderer::~VulkanRenderer()
{
    if (_enableValidationLayers)
    {
        destroyDebugUtilsMessengerEXT(_instance, _debugMessenger, nullptr);
    }
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
