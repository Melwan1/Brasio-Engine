#include <renderer/vulkan/builders/multisampling-builder.hh>

MultisamplingBuilder::MultisamplingBuilder()
{
    base();
}

MultisamplingBuilder &MultisamplingBuilder::base()
{
    _structureType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    return withSampleShadingEnable(VK_FALSE)
        .withRasterizationSamples(VK_SAMPLE_COUNT_1_BIT)
        .withMinSampleShading(1.0f)
        .withAlphaToCoverageEnable(VK_FALSE)
        .withAlphaToOneEnable(VK_FALSE);
}

MultisamplingBuilder &MultisamplingBuilder::withSampleShadingEnable(
    const VkBool32 &sampleShadingEnable)
{
    _sampleShadingEnable = sampleShadingEnable;
    return *this;
}

MultisamplingBuilder &MultisamplingBuilder::withRasterizationSamples(
    const VkSampleCountFlagBits &sampleCount)
{
    _sampleCount = sampleCount;
    return *this;
}

MultisamplingBuilder &
MultisamplingBuilder::withMinSampleShading(float minSampleShading)
{
    _minSampleShading = minSampleShading;
    return *this;
}

MultisamplingBuilder &MultisamplingBuilder::withAlphaToCoverageEnable(
    const VkBool32 &alphaToCoverageEnable)
{
    _alphaToCoverageEnable = alphaToCoverageEnable;
    return *this;
}

MultisamplingBuilder &
MultisamplingBuilder::withAlphaToOneEnable(const VkBool32 &alphaToOneEnable)
{
    _alphaToOneEnable = alphaToOneEnable;
    return *this;
}

VkPipelineMultisampleStateCreateInfo MultisamplingBuilder::build()
{
    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = _structureType;
    multisampling.sampleShadingEnable = _sampleShadingEnable;
    multisampling.rasterizationSamples = _sampleCount;
    multisampling.minSampleShading = _minSampleShading;
    multisampling.pSampleMask = nullptr;
    multisampling.alphaToCoverageEnable = _alphaToCoverageEnable;
    multisampling.alphaToOneEnable = _alphaToOneEnable;
    return multisampling;
}
