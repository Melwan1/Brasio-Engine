#pragma once

#include <filesystem>
#include <memory>

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>
#include <shaders/shader-manager.hh>

namespace brasio::renderer::vulkan
{
    class GraphicsPipeline : public core::Handler<VkPipeline>
    {
    public:
        GraphicsPipeline(const VkDevice &logicalDevice,
                         const VkGraphicsPipelineCreateInfo &createInfo);

        void bind(const VkCommandBuffer &commandBuffer);

    private:
    };

    using GraphicsPipelineType = std::unique_ptr<GraphicsPipeline>;
} // namespace brasio::renderer::vulkan
