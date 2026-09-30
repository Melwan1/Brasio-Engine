#include <shaders/shader-module.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::shaders
{
    ShaderModule::ShaderModule(const renderer::vulkan::VulkanRenderer &renderer,
                               const VkShaderModule &module,
                               const VkShaderStageFlagBits &shaderType)
        : core::Handler<VkShaderModule>(module, "shader module",
                                        [&renderer](const VkShaderModule &module) {
                                            vkDestroyShaderModule(renderer.getLogicalDevice(),
                                                                  module, nullptr);
                                        })
        , _shaderType(shaderType)
    {}

    const VkShaderStageFlagBits &ShaderModule::getShaderType() const
    {
        return _shaderType;
    }

    VkShaderStageFlagBits &ShaderModule::getShaderType()
    {
        return _shaderType;
    }
} // namespace brasio::shaders
