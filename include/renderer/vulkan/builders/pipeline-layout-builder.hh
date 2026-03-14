#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/pipeline-layout.hh>

namespace brasio::renderer::vulkan::builders
{
    class PipelineLayoutBuilder : public core::Builder<PipelineLayoutType>
    {
    public:
        PipelineLayoutBuilder(const VkDevice &logicalDevice);

        virtual PipelineLayoutBuilder &base() override;
        virtual PipelineLayoutType build() override;

        PipelineLayoutBuilder &
        withSetLayouts(const std::vector<VkDescriptorSetLayout> &setLayouts);
        PipelineLayoutBuilder &withPushConstantRanges(
            const std::vector<VkPushConstantRange> &pushConstantRanges);

    private:
        VkStructureType _structureType;
        VkDevice _logicalDevice;

        std::vector<VkDescriptorSetLayout> _setLayouts;
        std::vector<VkPushConstantRange> _pushConstantRanges;
    };
} // namespace brasio::renderer::vulkan::builders
