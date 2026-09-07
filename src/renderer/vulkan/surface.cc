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
        BRASIO_LOG_TRACE("Creating surface", { "CREATE" });
        if (glfwCreateWindowSurface(instance, window, nullptr, &getHandle())
            != VK_SUCCESS)
        {
            BRASIO_LOG_ERROR("Could not create surface",
                             { "CREATE" });
        }
        else
        {
            BRASIO_LOG_TRACE("Created surface", { "CREATE" });
        }
    }
} // namespace brasio::renderer::vulkan
