#include <renderer/vulkan/surface.hh>

#include <iostream>

#include <io/logging/logger.hh>

Surface::Surface(const VkInstance &instance, GLFWwindow *window)
    : _instance(instance)
    , _window(window)
    , _surface(VK_NULL_HANDLE)
{
    Logger::trace(std::cout, "Creating surface", { "CREATE" });
    if (glfwCreateWindowSurface(_instance, _window, nullptr, &_surface)
        != VK_SUCCESS)
    {
        Logger::error(std::cout, "Could not create surface", { "CREATE" });
    }
    else
    {
        Logger::trace(std::cout, "Created surface", { "CREATE" });
    }
}

Surface::~Surface()
{
    Logger::trace(std::cout, "Destroying surface", { "DESTROY" });
    vkDestroySurfaceKHR(_instance, _surface, nullptr);
    Logger::trace(std::cout, "Destroyed surface", { "DESTROY" });
}

const VkSurfaceKHR &Surface::getHandle() const
{
    return _surface;
}

VkSurfaceKHR &Surface::getHandle()
{
    return _surface;
}
