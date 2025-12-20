#include <renderer/vulkan_renderer.hh>

VulkanRenderer::VulkanRenderer()
{
    VkApplicationInfo application_info = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Brasio Engine",
        .applicationVersion = VK_MAKE_VERSION(0, 1, 0),
        .pEngineName = "Brasio Engine",
        .engineVersion = VK_MAKE_VERSION(0, 1, 0),
        .apiVersion = VK_API_VERSION_1_3,
        .pNext = nullptr
    };
}
