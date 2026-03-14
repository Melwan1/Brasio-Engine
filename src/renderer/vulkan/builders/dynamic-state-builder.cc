#include <renderer/vulkan/builders/dynamic-state-builder.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{
    DynamicStateBuilder::DynamicStateBuilder()
    {
        base();
    }

    DynamicStateBuilder &DynamicStateBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        return withDynamicStates(
            { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR });
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

        createInfo.dynamicStateCount =
            static_cast<uint32_t>(_dynamicStates.size());
        createInfo.pDynamicStates = _dynamicStates.data();
        return createInfo;
    }
} // namespace brasio::renderer::vulkan::builders
