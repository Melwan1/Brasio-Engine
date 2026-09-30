#include <renderer/vulkan/graphics-pipeline.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    GraphicsPipeline::GraphicsPipeline(const VulkanRenderer &renderer,
                                       const VkGraphicsPipelineCreateInfo &createInfo,
                                       PipelineLayoutType pipelineLayout)
        : Handler("graphics pipeline",
                  [&renderer](const VkPipeline &pipeline) {
                      vkDestroyPipeline(renderer.getLogicalDevice(), pipeline, nullptr);
                  })
        , _pipelineLayout(std::move(pipelineLayout))
    {
        BRASIO_LOG_TRACE("Creating graphics pipeline", { "CREATE" });

        BRASIO_VULKAN_CHECK(vkCreateGraphicsPipelines(renderer.getLogicalDevice(), VK_NULL_HANDLE,
                                                      1, &createInfo, nullptr, &getHandle()),
                            "create graphics pipeline", { "CREATE" });
        BRASIO_LOG_TRACE("Created graphics pipeline", { "CREATE" });
    }

    void GraphicsPipeline::bind(const VkCommandBuffer &commandBuffer) const
    {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, getHandle());
    }

    const PipelineLayout &GraphicsPipeline::getPipelineLayout() const
    {
        return *_pipelineLayout;
    }
} // namespace brasio::renderer::vulkan
