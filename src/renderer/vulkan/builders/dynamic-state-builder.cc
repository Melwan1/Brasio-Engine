#include <renderer/vulkan/builders/dynamic-state-builder.hh>

DynamicStateBuilder::DynamicStateBuilder()
{
    base();
}

DynamicStateBuilder &DynamicStateBuilder::base()
{
    _structureType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    _dynamicStates.clear();
    return *this;
}

DynamicStateBuilder &DynamicStateBuilder::withDynamicStates(
    const std::vector<VkDynamicState> &dynamicStates)
{
    _dynamicStates = dynamicStates;
    return *this;
}

VkPipelineDynamicStateCreateInfo DynamicStateBuilder::build()
{
    VkPipelineDynamicStateCreateInfo createInfo{};
    createInfo.sType = _structureType;
    createInfo.dynamicStateCount = _dynamicStates.size();
    createInfo.pDynamicStates = _dynamicStates.data();
    return createInfo;
}
