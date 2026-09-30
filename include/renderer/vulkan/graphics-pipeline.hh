#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>
#include <shaders/shader-manager.hh>
#include <renderer/vulkan/pipeline-layout.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class GraphicsPipeline : public core::Handler<VkPipeline>
    {
    public:
        GraphicsPipeline(const VulkanRenderer &renderer,
                         const VkGraphicsPipelineCreateInfo &createInfo,
                         PipelineLayoutType pipelineLayout);

        void bind(const VkCommandBuffer &commandBuffer) const;

        const PipelineLayout &getPipelineLayout() const;

    private:
        PipelineLayoutType _pipelineLayout;
    };

    using GraphicsPipelineType = std::unique_ptr<GraphicsPipeline>;
} // namespace brasio::renderer::vulkan
