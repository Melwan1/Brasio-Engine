#pragma once

#include <memory>
#include <core/handler.hh>
#include <vulkan/vulkan_core.h>
#include <renderer/vulkan/pipeline-layout.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class Pipeline : public core::Handler<VkPipeline>
    {
    public:
        Pipeline(const VulkanRenderer &renderer, PipelineLayoutType pipelineLayout);

        virtual void bind(const VkCommandBuffer &commandBuffer) const = 0;

        const PipelineLayout &getPipelineLayout() const;

    protected:
        const VulkanRenderer &_renderer;

    private:
        PipelineLayoutType _pipelineLayout;
    };

    using PipelineType = std::unique_ptr<Pipeline>;
} // namespace brasio::renderer::vulkan
