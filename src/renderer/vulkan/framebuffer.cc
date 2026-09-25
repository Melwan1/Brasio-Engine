#include <renderer/vulkan/framebuffer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    Framebuffer::Framebuffer(const LogicalDeviceType &logicalDevice,
                             const VkFramebufferCreateInfo &createInfo)
        : Handler("framebuffer",
                  [&logicalDevice](const VkFramebuffer &framebuffer) {
                      vkDestroyFramebuffer(logicalDevice->getHandle(),
                                           framebuffer, nullptr);
                  })
    {
        BRASIO_LOG_TRACE("Creating framebuffer", { "CREATE" });
        BRASIO_VULKAN_CHECK(vkCreateFramebuffer(logicalDevice->getHandle(),
                                                &createInfo, nullptr,
                                                &getHandle()),
                            "create framebuffer", { "CREATE" });
        BRASIO_LOG_TRACE("Created framebuffer", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
