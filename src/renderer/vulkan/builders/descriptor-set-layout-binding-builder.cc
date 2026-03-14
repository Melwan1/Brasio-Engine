#include <renderer/vulkan/builders/descriptor-set-layout-binding-builder.hh>

namespace brasio::renderer::vulkan::builders
{

    DescriptorSetLayoutBindingBuilder::DescriptorSetLayoutBindingBuilder()
    {
        base();
    }

    DescriptorSetLayoutBindingBuilder &DescriptorSetLayoutBindingBuilder::base()
    {
        return withBindingIndex(0)
            .withDescriptorType(VK_DESCRIPTOR_TYPE_MAX_ENUM)
            .withDescriptorCount(1);
    }

    DescriptorSetLayoutBindingBuilder &
    DescriptorSetLayoutBindingBuilder::withBindingIndex(uint32_t bindingIndex)
    {
        _bindingIndex = bindingIndex;
        return *this;
    }

    DescriptorSetLayoutBindingBuilder &
    DescriptorSetLayoutBindingBuilder::withDescriptorType(
        const VkDescriptorType &descriptorType)
    {
        _descriptorType = descriptorType;
        return *this;
    }

    DescriptorSetLayoutBindingBuilder &
    DescriptorSetLayoutBindingBuilder::withDescriptorCount(
        uint32_t descriptorCount)
    {
        _descriptorCount = descriptorCount;
        return *this;
    }

    DescriptorSetLayoutBindingBuilder &
    DescriptorSetLayoutBindingBuilder::withShaderStages(
        const VkShaderStageFlags &shaderStages)
    {
        _shaderStages = shaderStages;
        return *this;
    }

    VkDescriptorSetLayoutBinding DescriptorSetLayoutBindingBuilder::build()
    {
        VkDescriptorSetLayoutBinding binding{};
        binding.binding = _bindingIndex;
        binding.descriptorType = _descriptorType;
        binding.descriptorCount = _descriptorCount;
        binding.stageFlags = _shaderStages;
        binding.pImmutableSamplers = nullptr;
        return binding;
    }
} // namespace brasio::renderer::vulkan::builders
