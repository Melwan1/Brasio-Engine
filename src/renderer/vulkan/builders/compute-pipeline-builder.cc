#include <renderer/vulkan/builders/compute-pipeline-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    ComputePipelineBuilder::ComputePipelineBuilder(const LogicalDeviceType &logicalDevice,
                                                   const shaders::ShaderManager &shaderManager)
        : _logicalDevice(logicalDevice)
        , _shaderManager(shaderManager)
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
        VkPipelineShaderStageCreateInfo computeShaderStageInfo{};
        computeShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        computeShaderStageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
        computeShaderStageInfo.module =
            _shaderManager.createShaderModuleFromPath(_logicalDevice->getHandle(), _shaderPath);
        computeShaderStageInfo.pName = "main";

        VkComputePipelineCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.layout = _pipelineLayout->getHandle();
        createInfo.stage = computeShaderStageInfo;

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
        _shaderPath = shaderPath;
        return *this;
    }

} // namespace brasio::renderer::vulkan::builders
