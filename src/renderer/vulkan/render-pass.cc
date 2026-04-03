#include <renderer/vulkan/render-pass.hh>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan
{
    RenderPass::RenderPass(const VkDevice &logicalDevice,
                           const VkRenderPassCreateInfo &createInfo)
        : Handler("render pass",
                  [logicalDevice](const VkRenderPass &renderPass) {
                      vkDestroyRenderPass(logicalDevice, renderPass, nullptr);
                  })
    {
        BRASIO_LOG_TRACE(std::cout, "Creating render pass", { "CREATE" });
        if (vkCreateRenderPass(logicalDevice, &createInfo, nullptr,
                               &getHandle())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL(std::cout, "Could not create render pass",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE(std::cout, "Created render pass", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
