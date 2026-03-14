#pragma once

#include <filesystem>

#include <vulkan/vulkan_core.h>

#include <core/builder.hh>
#include <shaders/shader-module.hh>
#include <shaders/shader-manager.hh>

namespace fs = std::filesystem;

namespace brasio::renderer::vulkan::builders
{
    class PipelineShaderBuilder
        : public core::Builder<VkPipelineShaderStageCreateInfo>
    {
    public:
        PipelineShaderBuilder(const VkDevice &logicalDevice,
                              const shaders::ShaderManager &shaderManager);

        virtual PipelineShaderBuilder &base() override;
        virtual VkPipelineShaderStageCreateInfo build() override;

        PipelineShaderBuilder &
        withShaderType(const VkShaderStageFlagBits &shaderType);
        PipelineShaderBuilder &withShaderPath(const fs::path &shaderPath);
        PipelineShaderBuilder &withShader(const fs::path &shaderPath);

    private:
        VkDevice _logicalDevice;
        const shaders::ShaderManager &_shaderManager;

        VkStructureType _structureType;

        shaders::ShaderModuleType _shaderModule;

        fs::path _shaderPath;
        VkShaderStageFlagBits _shaderType;
    };
} // namespace brasio::renderer::vulkan::builders
