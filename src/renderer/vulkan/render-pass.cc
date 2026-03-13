#include <renderer/vulkan/render-pass.hh>

#include <io/logging/logger.hh>

RenderPass::RenderPass(const VkDevice &logicalDevice,
                       const VkRenderPassCreateInfo &createInfo)
    : Handler("render pass", [logicalDevice](const VkRenderPass &renderPass) {
        vkDestroyRenderPass(logicalDevice, renderPass, nullptr);
    })
{
    Logger::trace(std::cout, "Creating render pass", { "CREATE" });
    if (vkCreateRenderPass(logicalDevice, &createInfo, nullptr, &getHandle())
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create render pass",
                         { "CREATE" });
    }
    Logger::trace(std::cout, "Created render pass");
}
