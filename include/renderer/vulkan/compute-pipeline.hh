#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>
#include <shaders/shader-manager.hh>
#include <renderer/vulkan/pipeline-layout.hh>
#include <renderer/vulkan/command-buffer.hh>

namespace brasio::renderer::vulkan
{
    class ComputePipeline : public core::Handler<VkPipeline>
    {
    public:
        ComputePipeline(const VulkanRenderer &renderer,
                        const VkComputePipelineCreateInfo &createInfo,
                        PipelineLayoutType pipelineLayout);

        void bind(const VkCommandBuffer &commandBuffer) const;

        const PipelineLayout &getPipelineLayout() const;

    private:
        const VulkanRenderer &_renderer;
        PipelineLayoutType _pipelineLayout;
    };

    using ComputePipelineType = std::unique_ptr<ComputePipeline>;
} // namespace brasio::renderer::vulkan
