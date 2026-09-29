#include <renderer/vulkan/builders/pipeline-layout-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    PipelineLayoutBuilder::PipelineLayoutBuilder(const VkDevice &logicalDevice)
        : _logicalDevice(logicalDevice)
    {
        base();
    }

    PipelineLayoutBuilder &PipelineLayoutBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        _descriptorSetLayout.reset();
        _pushConstantRanges.clear();
        return *this;
    }

    PipelineLayoutBuilder &
    PipelineLayoutBuilder::withDescriptorSetLayout(DescriptorSetLayoutType descriptorSetLayout)
    {
        _descriptorSetLayout = std::move(descriptorSetLayout);
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
        if (_descriptorSetLayout)
        {
            setLayouts.push_back(_descriptorSetLayout->getHandle());
        }

        VkPipelineLayoutCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.setLayoutCount = setLayouts.size();
        createInfo.pSetLayouts = setLayouts.data();
        createInfo.pushConstantRangeCount = _pushConstantRanges.size();
        createInfo.pPushConstantRanges = _pushConstantRanges.data();

        return std::make_unique<PipelineLayout>(_logicalDevice, std::move(_descriptorSetLayout),
                                                createInfo);
    }
} // namespace brasio::renderer::vulkan::builders
