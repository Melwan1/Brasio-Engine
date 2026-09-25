#include <renderer/vulkan/surface.hh>

#include <io/logging/logger.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    Surface::Surface(const VkInstance &instance, GLFWwindow *window)
        : Handler("surface", [instance](const VkSurfaceKHR &surface) {
            vkDestroySurfaceKHR(instance, surface, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating surface", { "CREATE" });
        BRASIO_VULKAN_CHECK(glfwCreateWindowSurface(instance, window, nullptr, &getHandle()),
                            "create surface", { "CREATE" });
        BRASIO_LOG_TRACE("Created surface", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
