#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{
    class MultisamplingBuilder
        : public core::Builder<VkPipelineMultisampleStateCreateInfo>
    {
    public:
        MultisamplingBuilder();

        virtual MultisamplingBuilder &base() override;
        virtual VkPipelineMultisampleStateCreateInfo build() override;

        MultisamplingBuilder &
        withSampleShadingEnable(const VkBool32 &sampleShadingEnable);
        MultisamplingBuilder &
        withRasterizationSamples(const VkSampleCountFlagBits &sampleCount);
        MultisamplingBuilder &withMinSampleShading(float minSampleShading);
        MultisamplingBuilder &
        withAlphaToCoverageEnable(const VkBool32 &alphaToCoverageEnable);
        MultisamplingBuilder &
        withAlphaToOneEnable(const VkBool32 &alphaToOneEnable);

    private:
        VkStructureType _structureType;

        VkBool32 _sampleShadingEnable;
        VkSampleCountFlagBits _sampleCount;
        float _minSampleShading;
        VkBool32 _alphaToCoverageEnable;
        VkBool32 _alphaToOneEnable;
    };
} // namespace brasio::renderer::vulkan::builders
