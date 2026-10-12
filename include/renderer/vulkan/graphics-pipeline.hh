#pragma once

#include <memory>

#include <renderer/vulkan/pipeline.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class GraphicsPipeline : public Pipeline
    {
    public:
        GraphicsPipeline(const VulkanRenderer &renderer,
                         const VkGraphicsPipelineCreateInfo &createInfo,
                         PipelineLayoutType pipelineLayout);

        virtual void bind(const VkCommandBuffer &commandBuffer) const override;
    };

    using GraphicsPipelineType = std::unique_ptr<GraphicsPipeline>;
} // namespace brasio::renderer::vulkan
