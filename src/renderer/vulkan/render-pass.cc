#include <renderer/vulkan/render-pass.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    RenderPass::RenderPass(const VulkanRenderer &renderer, const VkRenderPassCreateInfo &createInfo)
        : Handler("render pass", [&renderer](const VkRenderPass &renderPass) {
            vkDestroyRenderPass(renderer.getLogicalDevice(), renderPass, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating render pass", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreateRenderPass(renderer.getLogicalDevice(), &createInfo, nullptr, &getHandle()),
            "create render pass", { "CREATE" });
        BRASIO_LOG_TRACE("Created render pass", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
