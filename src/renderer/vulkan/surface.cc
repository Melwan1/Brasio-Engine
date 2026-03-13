#include <renderer/vulkan/surface.hh>

#include <iostream>

#include <io/logging/logger.hh>

Surface::Surface(const VkInstance &instance, GLFWwindow *window)
    : Handler("surface", [instance](const VkSurfaceKHR &surface) {
        vkDestroySurfaceKHR(instance, surface, nullptr);
    })
{
    Logger::trace(std::cout, "Creating surface", { "CREATE" });
    if (glfwCreateWindowSurface(instance, window, nullptr, &getHandle())
        != VK_SUCCESS)
    {
        Logger::error(std::cout, "Could not create surface", { "CREATE" });
    }
    else
    {
        Logger::trace(std::cout, "Created surface", { "CREATE" });
    }
}
