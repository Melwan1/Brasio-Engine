#include <renderer/vulkan/builders/pipeline-layout-builder.hh>

PipelineLayoutBuilder::PipelineLayoutBuilder(const VkDevice &logicalDevice)
    : _logicalDevice(logicalDevice)
{
    base();
}

PipelineLayoutBuilder &PipelineLayoutBuilder::base()
{
    _structureType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    _setLayouts.clear();
    _pushConstantRanges.clear();
    return *this;
}

PipelineLayoutBuilder &PipelineLayoutBuilder::withSetLayouts(
    const std::vector<VkDescriptorSetLayout> &setLayouts)
{
    _setLayouts = setLayouts;
    return *this;
}

PipelineLayoutBuilder &PipelineLayoutBuilder::withPushConstantRanges(
    const std::vector<VkPushConstantRange> &pushConstantRanges)
{
    _pushConstantRanges = pushConstantRanges;
    return *this;
}

PipelineLayoutType PipelineLayoutBuilder::build()
{
    VkPipelineLayoutCreateInfo createInfo{};
    createInfo.sType = _structureType;
    createInfo.setLayoutCount = _setLayouts.size();
    createInfo.pSetLayouts = _setLayouts.data();
    createInfo.pushConstantRangeCount = _pushConstantRanges.size();
    createInfo.pPushConstantRanges = _pushConstantRanges.data();

    return std::make_unique<PipelineLayout>(_logicalDevice, createInfo);
}
