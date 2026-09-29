#include <renderer/vulkan/builders/descriptor-set-layout-binding-builder.hh>

namespace brasio::renderer::vulkan::builders
{

    uint32_t DescriptorSetLayoutBindingBuilder::_bindingIndex = 0;

    DescriptorSetLayoutBindingBuilder::DescriptorSetLayoutBindingBuilder()
    {
        base();
    }

    DescriptorSetLayoutBindingBuilder &DescriptorSetLayoutBindingBuilder::base()
    {
        return withDescriptorType(VK_DESCRIPTOR_TYPE_MAX_ENUM)
            .withDescriptorCount(1)
            .withImmutableSamplers(nullptr);
    }

    DescriptorSetLayoutBindingBuilder &
    DescriptorSetLayoutBindingBuilder::withDescriptorType(const VkDescriptorType &descriptorType)
    {
        _descriptorType = descriptorType;
        return *this;
    }

    DescriptorSetLayoutBindingBuilder &
    DescriptorSetLayoutBindingBuilder::withDescriptorCount(uint32_t descriptorCount)
    {
        _descriptorCount = descriptorCount;
        return *this;
    }

    DescriptorSetLayoutBindingBuilder &
    DescriptorSetLayoutBindingBuilder::withShaderStages(const VkShaderStageFlags &shaderStages)
    {
        _shaderStages = shaderStages;
        return *this;
    }

    DescriptorSetLayoutBindingBuilder &
    DescriptorSetLayoutBindingBuilder::withImmutableSamplers(VkSampler *samplers)
    {
        _samplers = samplers;
        return *this;
    }

    VkDescriptorSetLayoutBinding DescriptorSetLayoutBindingBuilder::build()
    {
        VkDescriptorSetLayoutBinding binding{};
        binding.binding = _bindingIndex++;
        binding.descriptorType = _descriptorType;
        binding.descriptorCount = _descriptorCount;
        binding.stageFlags = _shaderStages;
        binding.pImmutableSamplers = _samplers;
        return binding;
    }

    void DescriptorSetLayoutBindingBuilder::resetIndex()
    {
        _bindingIndex = 0;
    }
} // namespace brasio::renderer::vulkan::builders
