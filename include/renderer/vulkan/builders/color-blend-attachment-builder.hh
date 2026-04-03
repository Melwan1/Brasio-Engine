#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>
#include <yaml-cpp/yaml.h>

namespace brasio::renderer::vulkan::builders
{
    class ColorBlendAttachmentBuilder
        : public core::Builder<VkPipelineColorBlendAttachmentState>
    {
    public:
        ColorBlendAttachmentBuilder();

        virtual ColorBlendAttachmentBuilder &base() override;
        virtual VkPipelineColorBlendAttachmentState build() override;

        ColorBlendAttachmentBuilder &
        withColorWriteMask(const VkColorComponentFlags &colorWriteMask);
        ColorBlendAttachmentBuilder &
        withBlendEnable(const VkBool32 &blendEnable);
        ColorBlendAttachmentBuilder &
        withSrcColorBlendFactor(const VkBlendFactor &srcColorBlendFactor);
        ColorBlendAttachmentBuilder &
        withDstColorBlendFactor(const VkBlendFactor &dstColorBlendFactor);
        ColorBlendAttachmentBuilder &
        withColorBlendOp(const VkBlendOp &colorBlendOp);
        ColorBlendAttachmentBuilder &
        withSrcAlphaBlendFactor(const VkBlendFactor &srcAlphaBlendFactor);
        ColorBlendAttachmentBuilder &
        withDstAlphaBlendFactor(const VkBlendFactor &dstAlphaBlendFactor);
        ColorBlendAttachmentBuilder &
        withAlphaBlendOp(const VkBlendOp &alphaBlendOp);

        ColorBlendAttachmentBuilder &withConfig(const YAML::Node &config);

    private:
        VkColorComponentFlags _colorWriteMask;
        VkBool32 _blendEnable;
        VkBlendFactor _srcColorBlendFactor;
        VkBlendFactor _dstColorBlendFactor;
        VkBlendOp _colorBlendOp;
        VkBlendFactor _srcAlphaBlendFactor;
        VkBlendFactor _dstAlphaBlendFactor;
        VkBlendOp _alphaBlendOp;
    };
} // namespace brasio::renderer::vulkan::builders
