#include <renderer/vulkan/builders/pipeline-layout-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    PipelineLayoutBuilder::PipelineLayoutBuilder(const VulkanRenderer &renderer)
        : _renderer(renderer)
    {
        base();
    }

    PipelineLayoutBuilder &PipelineLayoutBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        _descriptorSetLayouts.clear();
        _pushConstantRanges.clear();
        return *this;
    }

    PipelineLayoutBuilder &
    PipelineLayoutBuilder::withDescriptorSetLayout(DescriptorSetLayoutType descriptorSetLayout)
    {
        _descriptorSetLayouts.emplace_back(std::move(descriptorSetLayout));
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
        std::vector<VkDescriptorSetLayout> setLayouts;
        for (const DescriptorSetLayoutType &descriptorSetLayout : _descriptorSetLayouts)
        {
            setLayouts.emplace_back(descriptorSetLayout->getHandle());
        }

        VkPipelineLayoutCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.setLayoutCount = setLayouts.size();
        createInfo.pSetLayouts = setLayouts.data();
        createInfo.pushConstantRangeCount = _pushConstantRanges.size();
        createInfo.pPushConstantRanges = _pushConstantRanges.data();

        return std::make_unique<PipelineLayout>(_renderer, std::move(_descriptorSetLayouts),
                                                createInfo);
    }
} // namespace brasio::renderer::vulkan::builders
