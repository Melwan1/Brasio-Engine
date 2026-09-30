#pragma once

#include <core/builder.hh>
#include <renderer/vulkan/compute-pipeline.hh>
#include <renderer/vulkan/builders/pipeline-shader-info-builder.hh>

#include <filesystem>

namespace fs = std::filesystem;

namespace brasio::renderer::vulkan::builders
{
    class ComputePipelineBuilder : public core::Builder<ComputePipelineType>
    {
    public:
        ComputePipelineBuilder(const VulkanRenderer &renderer);
        virtual ComputePipelineBuilder &base() override;
        virtual ComputePipelineType build() override;

        ComputePipelineBuilder &withPipelineLayout(PipelineLayoutType pipelineLayout);
        ComputePipelineBuilder &withShader(const fs::path &shaderPath);

    private:
        const VulkanRenderer &_renderer;
        VkStructureType _structureType;
        PipelineLayoutType _pipelineLayout;

        PipelineShaderBuilder _pipelineShaderBuilder;
    };
} // namespace brasio::renderer::vulkan::builders
