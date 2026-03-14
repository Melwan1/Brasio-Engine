#include <renderer/vulkan/surface.hh>

#include <iostream>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan
{
    Surface::Surface(const VkInstance &instance, GLFWwindow *window)
        : Handler("surface", [instance](const VkSurfaceKHR &surface) {
            vkDestroySurfaceKHR(instance, surface, nullptr);
        })
    {
        io::logging::Logger::trace(std::cout, "Creating surface", { "CREATE" });
        if (glfwCreateWindowSurface(instance, window, nullptr, &getHandle())
            != VK_SUCCESS)
        {
            io::logging::Logger::error(std::cout, "Could not create surface",
                                       { "CREATE" });
        }
        else
        {
            io::logging::Logger::trace(std::cout, "Created surface",
                                       { "CREATE" });
        }
    }
} // namespace brasio::renderer::vulkan
