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

    DynamicStateBuilder &
    DynamicStateBuilder::withConfig(const YAML::Node &config)
    {
        std::map<std::string, VkDynamicState> map = {
            { "VIEWPORT", VK_DYNAMIC_STATE_VIEWPORT },
            { "SCISSOR", VK_DYNAMIC_STATE_SCISSOR },
        };

        std::vector<VkDynamicState> dynamicStates{};
        for (const YAML::Node &dynamicStateStr : config)
        {
            dynamicStates.emplace_back(
                map.at(dynamicStateStr.as<std::string>()));
        }
        return withDynamicStates(dynamicStates);
    }

    VkPipelineDynamicStateCreateInfo DynamicStateBuilder::build()
    {
        VkPipelineDynamicStateCreateInfo createInfo{};

        createInfo.sType = _structureType;
        createInfo.dynamicStateCount =
            static_cast<uint32_t>(_dynamicStates.size());
        createInfo.pDynamicStates = _dynamicStates.data();
        return createInfo;
    }

} // namespace brasio::renderer::vulkan::builders
