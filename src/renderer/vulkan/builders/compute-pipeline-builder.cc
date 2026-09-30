#include <renderer/vulkan/builders/compute-pipeline-builder.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::renderer::vulkan::builders
{
    ComputePipelineBuilder::ComputePipelineBuilder(const VulkanRenderer &renderer)
        : _renderer(renderer)
        , _pipelineShaderBuilder(renderer)
    {
        base();
    }

    ComputePipelineBuilder &ComputePipelineBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        return *this;
    }

    ComputePipelineType ComputePipelineBuilder::build()
    {
        VkComputePipelineCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.layout = _pipelineLayout->getHandle();
        createInfo.stage = _pipelineShaderBuilder.build();

        return std::make_unique<ComputePipeline>(_renderer, createInfo, std::move(_pipelineLayout));
    }

    ComputePipelineBuilder &
    ComputePipelineBuilder::withPipelineLayout(PipelineLayoutType pipelineLayout)
    {
        _pipelineLayout = std::move(pipelineLayout);
        return *this;
    }

    ComputePipelineBuilder &ComputePipelineBuilder::withShader(const fs::path &shaderPath)
    {
        _pipelineShaderBuilder.withShader(shaderPath);
        return *this;
    }

} // namespace brasio::renderer::vulkan::builders
