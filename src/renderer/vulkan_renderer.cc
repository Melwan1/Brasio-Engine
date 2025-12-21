#include <renderer/vulkan_renderer.hh>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include <iostream>

VulkanRenderer::VulkanRenderer()
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

    createInfo.enabledLayerCount = 0; // FIXME, only temporary

    vkEnumerateInstanceExtensionProperties(nullptr, &_extensionCount, nullptr);
    _extensions.resize(_extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &_extensionCount,
                                           _extensions.data());

    print_extensions(std::cout);

    if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create instance!");
    }
}

void VulkanRenderer::init()
{}

VulkanRenderer::~VulkanRenderer()
{
    vkDestroyInstance(_instance, nullptr);
}

void VulkanRenderer::print_extensions(std::ostream &ostr)
{
    ostr << "Available Vulkan Instance Extensions:";
    for (auto &extension : _extensions)
    {
        ostr << extension.extensionName << ", ";
    }
    ostr << std::endl;
}
