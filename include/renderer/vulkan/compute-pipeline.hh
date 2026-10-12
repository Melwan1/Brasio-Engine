#pragma once

#include <memory>

#include <renderer/vulkan/pipeline.hh>

namespace brasio::renderer::vulkan
{
    class ComputePipeline : public Pipeline
    {
    public:
        ComputePipeline(const VulkanRenderer &renderer,
                        const VkComputePipelineCreateInfo &createInfo,
                        PipelineLayoutType pipelineLayout);

        virtual void bind(const VkCommandBuffer &commandBuffer) const override;
    };

    using ComputePipelineType = std::unique_ptr<ComputePipeline>;
} // namespace brasio::renderer::vulkan
