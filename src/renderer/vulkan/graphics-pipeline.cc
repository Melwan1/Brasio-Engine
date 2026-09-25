#include <renderer/vulkan/graphics-pipeline.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    GraphicsPipeline::GraphicsPipeline(const VkDevice &logicalDevice,
                                       const VkGraphicsPipelineCreateInfo &createInfo)
        : Handler("graphics pipeline", [logicalDevice](const VkPipeline &pipeline) {
            vkDestroyPipeline(logicalDevice, pipeline, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating graphics pipeline", { "CREATE" });

        uint32_t pipelineCreateInfoCount = 1;
        BRASIO_VULKAN_CHECK(vkCreateGraphicsPipelines(logicalDevice, VK_NULL_HANDLE,
                                                      pipelineCreateInfoCount, &createInfo, nullptr,
                                                      &getHandle()),
                            "create graphics pipeline", { "CREATE" });
        BRASIO_LOG_TRACE("Created graphics pipeline", { "CREATE" });
    }

    void GraphicsPipeline::bind(const VkCommandBuffer &commandBuffer) const
    {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, getHandle());
    }
} // namespace brasio::renderer::vulkan
