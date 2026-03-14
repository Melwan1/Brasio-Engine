#include <renderer/vulkan/builders/input-assembly-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    InputAssemblyBuilder::InputAssemblyBuilder()
    {
        base();
    }

    InputAssemblyBuilder &InputAssemblyBuilder::base()
    {
        _structureType =
            VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;

        return withPrimitiveRestartEnable(VK_FALSE).withPrimitiveTopology(
            VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
    }

    InputAssemblyBuilder &
    InputAssemblyBuilder::withPrimitiveRestartEnable(const VkBool32 &enabled)
    {
        _primitiveRestartEnable = enabled;
        return *this;
    }

    InputAssemblyBuilder &InputAssemblyBuilder::withPrimitiveTopology(
        const VkPrimitiveTopology &topology)
    {
        _primitiveTopology = topology;
        return *this;
    }

    VkPipelineInputAssemblyStateCreateInfo InputAssemblyBuilder::build()
    {
        VkPipelineInputAssemblyStateCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.topology = _primitiveTopology;
        createInfo.primitiveRestartEnable = _primitiveRestartEnable;
        return createInfo;
    }
} // namespace brasio::renderer::vulkan::builders
