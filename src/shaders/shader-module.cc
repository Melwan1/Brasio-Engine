#include <shaders/shader-module.hh>

#include <io/logging/logger.hh>

namespace brasio::shaders
{
    ShaderModule::ShaderModule(VkDevice &device, const VkShaderModule &module,
                               const VkShaderStageFlagBits &shaderType)
        : core::Handler<VkShaderModule>(module, "shader module",
                                        [device](const VkShaderModule &module) {
                                            vkDestroyShaderModule(
                                                device, module, nullptr);
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
