#include <shaders/shader-module.hh>

#include <io/logging/logger.hh>

ShaderModule::ShaderModule(VkDevice &device, const VkShaderModule &module)
    : Handler(module, "shader module", [device](const VkShaderModule &module) {
        vkDestroyShaderModule(device, module, nullptr);
    })
{}
