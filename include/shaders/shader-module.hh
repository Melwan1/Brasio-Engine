#pragma once

#include <vulkan/vulkan.hpp>

class ShaderModule
{
public:
    ShaderModule(VkDevice &device, VkShaderModule vulkanModule);

    ~ShaderModule();

    const VkShaderModule& getVulkanModule();
private:
    VkShaderModule _vulkanModule;
    VkDevice _device;
};