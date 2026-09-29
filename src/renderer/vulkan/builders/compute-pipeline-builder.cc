#include <renderer/vulkan/builders/compute-pipeline-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    ComputePipelineBuilder::ComputePipelineBuilder(const LogicalDeviceType &logicalDevice,
                                                   const shaders::ShaderManager &shaderManager)
        : _logicalDevice(logicalDevice)
        , _pipelineShaderBuilder(_logicalDevice->getHandle(), shaderManager)
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

        return std::make_unique<ComputePipeline>(_logicalDevice, createInfo,
                                                 std::move(_pipelineLayout));
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
