#include <shaders/shader-module.hh>

ShaderModule::ShaderModule(VkDevice &device, VkShaderModule vulkanModule)
    : _vulkanModule(vulkanModule)
    , _device(device)
{}

ShaderModule::~ShaderModule()
{
    vkDestroyShaderModule(_device, _vulkanModule, nullptr);
}

const VkShaderModule &ShaderModule::getVulkanModule()
{
    return _vulkanModule;
}