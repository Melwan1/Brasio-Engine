#include <renderer/vulkan/render-pass.hh>

#include <io/logging/logger.hh>

RenderPass::RenderPass(const VkDevice &logicalDevice,
                       const VkRenderPassCreateInfo &createInfo)
    : _logicalDevice(logicalDevice)
{
    Logger::trace(std::cout, "Creating render pass", { "CREATE" });
    if (vkCreateRenderPass(_logicalDevice, &createInfo, nullptr, &_renderPass)
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create render pass",
                         { "CREATE" });
    }
    Logger::trace(std::cout, "Created render pass");
}

RenderPass::~RenderPass()
{
    Logger::trace(std::cout, "Destroying render pass", { "DESTROY" });
    vkDestroyRenderPass(_logicalDevice, _renderPass, nullptr);
    Logger::trace(std::cout, "Destroyed render pass", { "DESTROY" });
}

const VkRenderPass &RenderPass::getHandle() const
{
    return _renderPass;
}

VkRenderPass &RenderPass::getHandle()
{
    return _renderPass;
}
