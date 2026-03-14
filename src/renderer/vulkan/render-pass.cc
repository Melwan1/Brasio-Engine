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
        io::logging::Logger::trace(std::cout, "Creating render pass",
                                   { "CREATE" });
        if (vkCreateRenderPass(logicalDevice, &createInfo, nullptr,
                               &getHandle())
            != VK_SUCCESS)
        {
            io::logging::Logger::critical(
                std::cout, "Could not create render pass", { "CREATE" });
        }
        io::logging::Logger::trace(std::cout, "Created render pass",
                                   { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
