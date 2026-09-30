#include <renderer/vulkan/surface.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    Surface::Surface(const VulkanRenderer &renderer)
        : Handler("surface", [&renderer](const VkSurfaceKHR &surface) {
            vkDestroySurfaceKHR(renderer.getInstance(), surface, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating surface", { "CREATE" });
        BRASIO_VULKAN_CHECK(glfwCreateWindowSurface(renderer.getInstance(), renderer.getWindow(),
                                                    nullptr, &getHandle()),
                            "create surface", { "CREATE" });
        BRASIO_LOG_TRACE("Created surface", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
