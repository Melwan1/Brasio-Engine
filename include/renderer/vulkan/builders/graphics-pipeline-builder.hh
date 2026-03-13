#pragma once

#include <core/builder.hh>
#include <renderer/vulkan/graphics-pipeline.hh>
#include <renderer/vulkan/builders/all.hh>

#include <geometry/vertex.hh>

class GraphicsPipelineBuilder : public Builder<GraphicsPipelineType>
{
public:
    GraphicsPipelineBuilder(const VkDevice &logicalDevice,
                            const ShaderManager &shaderManager,
                            const VkPipelineLayout &pipelineLayout,
                            const VkRenderPass &renderPass);

    virtual GraphicsPipelineType build() override;
    virtual GraphicsPipelineBuilder &base() override;

    GraphicsPipelineBuilder &
    withShaders(const std::vector<fs::path> &shaderPaths);

private:
    VkDevice _logicalDevice;
    const ShaderManager &_shaderManager;
    const VkPipelineLayout &_pipelineLayout;
    const VkRenderPass &_renderPass;

    VkStructureType _structureType;

    std::vector<PipelineShaderBuilder> _shaderBuilders{};
    std::vector<VkPipelineShaderStageCreateInfo> _shaderInfos;

    DynamicStateBuilder _dynamicStateBuilder;
    VertexInputBuilder _vertexInputBuilder;
    InputAssemblyBuilder _inputAssemblyBuilder;
    ViewportStateBuilder _viewportStateBuilder;
    RasterizerBuilder _rasterizerBuilder;
    MultisamplingBuilder _multisamplingBuilder;
    ColorBlendAttachmentBuilder _colorBlendAttachmentBuilder;
    ColorBlendStateBuilder _colorBlendStateBuilder;
    PipelineLayoutBuilder _pipelineLayoutBuilder;

    std::vector<fs::path> _shaderPaths;

    bool _checkUniqueShaderType(const std::string &extension);
};
