#include <renderer/vulkan/builders/descriptor-set-layout-builder.hh>
#include <renderer/vulkan/builders/descriptor-set-layout-binding-builder.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{

    DescriptorSetLayoutBuilder::DescriptorSetLayoutBuilder(const VulkanRenderer &renderer)
        : _renderer(renderer)
    {
        base();
    }

    DescriptorSetLayoutBuilder &DescriptorSetLayoutBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        _bindings.clear();
        return *this;
    }

    DescriptorSetLayoutBuilder &DescriptorSetLayoutBuilder::withBindings(
        const std::vector<VkDescriptorSetLayoutBinding> &bindings)
    {
        _bindings = bindings;
        return *this;
    }

    DescriptorSetLayoutBuilder &
    DescriptorSetLayoutBuilder::withUniformBuffers(uint32_t uniformBufferCount,
                                                   VkShaderStageFlagBits shaderStage)
    {
        for (uint32_t uniformIndex = 0; uniformIndex < uniformBufferCount; uniformIndex++)
        {
            _bindings.emplace_back(DescriptorSetLayoutBindingBuilder()
                                       .withDescriptorType(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
                                       .withShaderStages(shaderStage)
                                       .build());
        }
        return *this;
    }

    DescriptorSetLayoutBuilder &
    DescriptorSetLayoutBuilder::withStorageBuffers(uint32_t storageBufferCount,
                                                   VkShaderStageFlagBits shaderStage)
    {
        for (uint32_t storageIndex = 0; storageIndex < storageBufferCount; storageIndex++)
        {
            _bindings.emplace_back(DescriptorSetLayoutBindingBuilder()
                                       .withDescriptorType(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER)
                                       .withShaderStages(shaderStage)
                                       .build());
        }
        return *this;
    }

    DescriptorSetLayoutBuilder &
    DescriptorSetLayoutBuilder::withTextures(uint32_t textureCount,
                                             VkShaderStageFlagBits shaderStage)
    {
        for (uint32_t textureIndex = 0; textureIndex < textureCount; textureIndex++)
        {
            _bindings.emplace_back(
                DescriptorSetLayoutBindingBuilder()
                    .withDescriptorType(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
                    .withShaderStages(shaderStage)
                    .build());
        }
        return *this;
    }

    DescriptorSetLayoutType DescriptorSetLayoutBuilder::build()
    {
        VkDescriptorSetLayoutCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.bindingCount = _bindings.size();
        createInfo.pBindings = _bindings.data();

        return std::make_unique<DescriptorSetLayout>(_renderer, createInfo);
    }

} // namespace brasio::renderer::vulkan::builders
