#pragma once

#include <vulkan/vulkan.hpp>

#include <core/handler.hh>

class ShaderModule : public Handler<VkShaderModule>
{
public:
    ShaderModule(VkDevice &device, const VkShaderModule &module);

private:
    VkDevice _device;
};
