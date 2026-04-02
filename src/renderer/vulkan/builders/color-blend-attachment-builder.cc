#include <renderer/vulkan/builders/color-blend-attachment-builder.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{
    ColorBlendAttachmentBuilder::ColorBlendAttachmentBuilder()
    {
        base();
    }

    ColorBlendAttachmentBuilder &ColorBlendAttachmentBuilder::base()
    {
        return withColorWriteMask(
                   VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT
                   | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT)
            .withBlendEnable(VK_FALSE)
            .withSrcColorBlendFactor(VK_BLEND_FACTOR_ONE)
            .withDstColorBlendFactor(VK_BLEND_FACTOR_ZERO)
            .withColorBlendOp(VK_BLEND_OP_ADD)
            .withSrcAlphaBlendFactor(VK_BLEND_FACTOR_ONE)
            .withDstAlphaBlendFactor(VK_BLEND_FACTOR_ZERO)
            .withAlphaBlendOp(VK_BLEND_OP_ADD);
    }

    ColorBlendAttachmentBuilder &
    ColorBlendAttachmentBuilder::withColorWriteMask(
        const VkColorComponentFlags &colorWriteMask)
    {
        _colorWriteMask = colorWriteMask;
        return *this;
    }

    ColorBlendAttachmentBuilder &
    ColorBlendAttachmentBuilder::withBlendEnable(const VkBool32 &blendEnable)
    {
        _blendEnable = blendEnable;
        return *this;
    }

    ColorBlendAttachmentBuilder &
    ColorBlendAttachmentBuilder::withSrcColorBlendFactor(
        const VkBlendFactor &srcColorBlendFactor)
    {
        _srcColorBlendFactor = srcColorBlendFactor;
        return *this;
    }

    ColorBlendAttachmentBuilder &
    ColorBlendAttachmentBuilder::withDstColorBlendFactor(
        const VkBlendFactor &dstColorBlendFactor)
    {
        _dstColorBlendFactor = dstColorBlendFactor;
        return *this;
    }

    ColorBlendAttachmentBuilder &
    ColorBlendAttachmentBuilder::withColorBlendOp(const VkBlendOp &colorBlendOp)
    {
        _colorBlendOp = colorBlendOp;
        return *this;
    }

    ColorBlendAttachmentBuilder &
    ColorBlendAttachmentBuilder::withSrcAlphaBlendFactor(
        const VkBlendFactor &srcAlphaBlendFactor)
    {
        _srcAlphaBlendFactor = srcAlphaBlendFactor;
        return *this;
    }

    ColorBlendAttachmentBuilder &
    ColorBlendAttachmentBuilder::withDstAlphaBlendFactor(
        const VkBlendFactor &dstAlphaBlendFactor)
    {
        _dstAlphaBlendFactor = dstAlphaBlendFactor;
        return *this;
    }

    ColorBlendAttachmentBuilder &
    ColorBlendAttachmentBuilder::withAlphaBlendOp(const VkBlendOp &alphaBlendOp)
    {
        _alphaBlendOp = alphaBlendOp;
        return *this;
    }

    ColorBlendAttachmentBuilder &
    ColorBlendAttachmentBuilder::withConfig(const YAML::Node &config)
    {
        std::map<char, VkColorComponentFlags> sampleMaskMap = {
            { 'R', VK_COLOR_COMPONENT_R_BIT },
            { 'G', VK_COLOR_COMPONENT_G_BIT },
            { 'B', VK_COLOR_COMPONENT_B_BIT },
            { 'A', VK_COLOR_COMPONENT_A_BIT }
        };
        VkColorComponentFlags colorMask = 0;
        for (char c : config["writeMask"].as<std::string>())
        {
            colorMask |= sampleMaskMap.at(c);
        }

        std::map<std::string, VkBlendFactor> blendFactorMap = {
            { "ZERO", VK_BLEND_FACTOR_ZERO }, { "ONE", VK_BLEND_FACTOR_ONE }
        };

        std::map<std::string, VkBlendOp> blendOpMap = { { "ADD",
                                                          VK_BLEND_OP_ADD } };

        return withColorWriteMask(colorMask)
            .withBlendEnable(config["blend"].as<bool>())
            .withSrcColorBlendFactor(blendFactorMap.at(
                config["src_color_blend_factor"].as<std::string>()))
            .withDstColorBlendFactor(blendFactorMap.at(
                config["dst_color_blend_factor"].as<std::string>()))
            .withColorBlendOp(
                blendOpMap.at(config["color_blend_op"].as<std::string>()))
            .withSrcAlphaBlendFactor(blendFactorMap.at(
                config["src_alpha_blend_factor"].as<std::string>()))
            .withDstAlphaBlendFactor(blendFactorMap.at(
                config["dst_alpha_blend_factor"].as<std::string>()))
            .withAlphaBlendOp(
                blendOpMap.at(config["alpha_blend_op"].as<std::string>()));
    }

    VkPipelineColorBlendAttachmentState ColorBlendAttachmentBuilder::build()
    {
        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = _colorWriteMask;
        colorBlendAttachment.blendEnable = _blendEnable;
        colorBlendAttachment.srcColorBlendFactor = _srcColorBlendFactor;
        colorBlendAttachment.dstColorBlendFactor = _dstColorBlendFactor;
        colorBlendAttachment.colorBlendOp = _colorBlendOp;
        colorBlendAttachment.srcAlphaBlendFactor = _srcAlphaBlendFactor;
        colorBlendAttachment.dstAlphaBlendFactor = _dstAlphaBlendFactor;
        colorBlendAttachment.alphaBlendOp = _alphaBlendOp;
        return colorBlendAttachment;
    }

} // namespace brasio::renderer::vulkan::builders
