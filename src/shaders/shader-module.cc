#include <shaders/shader-module.hh>

#include <io/logging/logger.hh>

ShaderModule::ShaderModule(VkDevice &device, const VkShaderModule &module)
    : Handler(module, "shader module",
              [&device, module]() {
                  vkDestroyShaderModule(device, module, nullptr);
              })
    , _device(device)
{}
