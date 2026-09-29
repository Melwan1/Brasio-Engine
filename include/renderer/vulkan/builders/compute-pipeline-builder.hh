#pragma once

#include <core/builder.hh>
#include <renderer/vulkan/compute-pipeline.hh>

#include <filesystem>

namespace fs = std::filesystem;

namespace brasio::renderer::vulkan::builders
{
    class ComputePipelineBuilder : public core::Builder<ComputePipelineType>
    {
    public:
        ComputePipelineBuilder(const LogicalDeviceType &logicalDevice,
                               const shaders::ShaderManager &shaderManager);
        virtual ComputePipelineBuilder &base() override;
        virtual ComputePipelineType build() override;

        ComputePipelineBuilder &withPipelineLayout(PipelineLayoutType pipelineLayout);
        ComputePipelineBuilder &withShader(const fs::path &shaderPath);

    private:
        const LogicalDeviceType &_logicalDevice;
        const shaders::ShaderManager &_shaderManager;
        VkStructureType _structureType;
        PipelineLayoutType _pipelineLayout;
        fs::path _shaderPath;
    };
} // namespace brasio::renderer::vulkan::builders
