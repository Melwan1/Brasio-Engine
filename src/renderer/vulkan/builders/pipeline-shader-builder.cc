#include <renderer/vulkan/builders/pipeline-shader-info.hh>
#include <vulkan/vulkan_core.h>

PipelineShaderInfoBuilder::PipelineShaderInfoBuilder(
    const VkDevice &logicalDevice, const ShaderManager &shaderManager)
    : _logicalDevice(logicalDevice)
    , _shaderManager(shaderManager)
    , _structureType(VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO)
{}

VkPipelineShaderStageCreateInfo PipelineShaderInfoBuilder::build()
{
    VkPipelineShaderStageCreateInfo shaderStageInfo{};
    shaderStageInfo.sType = _structureType;
    shaderStageInfo.stage = _shaderModule->getShaderType();
    shaderStageInfo.module = _shaderModule->getHandle();
    shaderStageInfo.pName = "main";
    return shaderStageInfo;
}

PipelineShaderInfoBuilder &
PipelineShaderInfoBuilder::withShader(const fs::path &shaderPath)
{
    static std::map<std::string, VkShaderStageFlagBits>
        shaderStageByExtension = {
            { "vert", VK_SHADER_STAGE_VERTEX_BIT },
            { "frag", VK_SHADER_STAGE_FRAGMENT_BIT },
            { "comp", VK_SHADER_STAGE_COMPUTE_BIT },
            { "geom", VK_SHADER_STAGE_GEOMETRY_BIT },
            { "tctl", VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT },
            { "tval", VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT }
        };
    withShaderPath(shaderPath)
        .withShaderType(shaderStageByExtension.at(
            shaderPath.extension().string().substr(1)));
    _shaderModule = std::make_unique<ShaderModule>(
        _logicalDevice,
        _shaderManager.createShaderModuleFromPath(_logicalDevice, shaderPath),
        _shaderType);
    return *this;
}

PipelineShaderInfoBuilder &
PipelineShaderInfoBuilder::withShaderPath(const fs::path &shaderPath)
{
    _shaderPath = shaderPath;
    return *this;
}

PipelineShaderInfoBuilder &PipelineShaderInfoBuilder::withShaderType(
    const VkShaderStageFlagBits &shaderType)
{
    _shaderType = shaderType;
    return *this;
}
