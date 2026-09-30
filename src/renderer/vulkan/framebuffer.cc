#include <renderer/vulkan/framebuffer.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    Framebuffer::Framebuffer(const VulkanRenderer &renderer,
                             const VkFramebufferCreateInfo &createInfo)
        : Handler("framebuffer", [&renderer](const VkFramebuffer &framebuffer) {
            vkDestroyFramebuffer(renderer.getLogicalDevice(), framebuffer, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating framebuffer", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreateFramebuffer(renderer.getLogicalDevice(), &createInfo, nullptr, &getHandle()),
            "create framebuffer", { "CREATE" });
        BRASIO_LOG_TRACE("Created framebuffer", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
