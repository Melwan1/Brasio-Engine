#include <renderer/vulkan/render-pass.hh>

#include <io/logging/logger.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    RenderPass::RenderPass(const VkDevice &logicalDevice,
                           const VkRenderPassCreateInfo &createInfo)
        : Handler("render pass",
                  [logicalDevice](const VkRenderPass &renderPass) {
                      vkDestroyRenderPass(logicalDevice, renderPass, nullptr);
                  })
    {
        BRASIO_LOG_TRACE("Creating render pass", { "CREATE" });
        BRASIO_VULKAN_CHECK(vkCreateRenderPass(logicalDevice, &createInfo,
                                               nullptr, &getHandle()),
                            "create render pass", { "CREATE" });
        BRASIO_LOG_TRACE("Created render pass", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
