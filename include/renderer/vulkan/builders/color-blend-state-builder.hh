#pragma once

#include <core/builder.hh>

#include <vector>

#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{
    class ColorBlendStateBuilder
        : public core::Builder<VkPipelineColorBlendStateCreateInfo>
    {
    public:
        ColorBlendStateBuilder();

        virtual ColorBlendStateBuilder &base() override;
        virtual VkPipelineColorBlendStateCreateInfo build() override;

        ColorBlendStateBuilder &
        withLogicOpEnable(const VkBool32 &logicOpEnable);
        ColorBlendStateBuilder &withLogicOp(const VkLogicOp &logicOp);
        ColorBlendStateBuilder &withColorBlendAttachments(
            const std::vector<VkPipelineColorBlendAttachmentState>
                &colorBlendAttachments);

    private:
        VkStructureType _structureType;

        VkBool32 _logicOpEnable;
        VkLogicOp _logicOp;
        std::vector<VkPipelineColorBlendAttachmentState> _colorBlendAttachments;
    };
} // namespace brasio::renderer::vulkan::builders
