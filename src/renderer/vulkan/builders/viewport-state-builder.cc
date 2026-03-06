#include <renderer/vulkan/builders/viewport-state-builder.hh>

ViewportStateBuilder::ViewportStateBuilder()
{
    base();
}

ViewportStateBuilder &ViewportStateBuilder::base()
{
    _structureType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

    return withViewports(1).withScissors(1);
}

ViewportStateBuilder &
ViewportStateBuilder::withViewports(uint32_t viewportCount)
{
    _viewportCount = viewportCount;
    return *this;
}

ViewportStateBuilder &ViewportStateBuilder::withScissors(uint32_t scissorCount)
{
    _scissorCount = scissorCount;
    return *this;
}

VkPipelineViewportStateCreateInfo ViewportStateBuilder::build()
{
    VkPipelineViewportStateCreateInfo createInfo{};
    createInfo.sType = _structureType;
    createInfo.viewportCount = 1;
    createInfo.scissorCount = 1;
    return createInfo;
}
