#include <renderer/vulkan_renderer.hh>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include <algorithm>
#include <iostream>

VulkanRenderer::VulkanRenderer()
{
    createInstance();
}

void VulkanRenderer::init()
{}

VulkanRenderer::~VulkanRenderer()
{
    vkDestroyInstance(_instance, nullptr);
}

void VulkanRenderer::printExtensions(std::ostream &ostr)
{
    ostr << "Available Vulkan Instance Extensions:";
    for (auto &extension : _extensions)
    {
        ostr << extension.extensionName << ", ";
    }
    ostr << std::endl;
}

void VulkanRenderer::createInstance()
{
    VkApplicationInfo applicationInfo{};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = "Brasio Engine";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    applicationInfo.pEngineName = "Brasio Engine";
    applicationInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    applicationInfo.apiVersion = VK_API_VERSION_1_3;
    applicationInfo.pNext = nullptr;

    VkInstanceCreateInfo createInfo{};

    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &applicationInfo;

    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions =
        glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    vkEnumerateInstanceExtensionProperties(nullptr, &_extensionCount, nullptr);
    _extensions.resize(_extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &_extensionCount,
                                           _extensions.data());

    printExtensions(std::cout);

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    if (enableValidationLayers && !checkValidationLayerSupport())
    {
        throw std::runtime_error("Validation layers requested but not found.");
    }

    if (enableValidationLayers)
    {
        createInfo.enabledLayerCount = _validationLayers.size();
        createInfo.ppEnabledLayerNames = _validationLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
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
