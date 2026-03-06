#pragma once

#include <memory>

#include <vulkan/vulkan.hpp>

#include <core/handler.hh>

class ShaderModule : public Handler<VkShaderModule>
{
public:
    ShaderModule(VkDevice &device, const VkShaderModule &module,
                 const VkShaderStageFlagBits &shaderType);

    const VkShaderStageFlagBits &getShaderType() const;
    VkShaderStageFlagBits &getShaderType();

private:
    VkShaderStageFlagBits _shaderType;
};

using ShaderModuleType = std::unique_ptr<ShaderModule>;
