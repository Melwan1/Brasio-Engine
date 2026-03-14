#include <renderer/vulkan/graphics-pipeline.hh>

namespace brasio::renderer::vulkan
{
    GraphicsPipeline::GraphicsPipeline(
        const VkDevice &logicalDevice,
        const VkGraphicsPipelineCreateInfo &createInfo)
        : Handler("graphics pipeline",
                  [logicalDevice](const VkPipeline &pipeline) {
                      vkDestroyPipeline(logicalDevice, pipeline, nullptr);
                  })
    {
        io::logging::Logger::trace(std::cout, "Creating graphics pipeline",
                                   { "CREATE" });

        uint32_t pipelineCreateInfoCount = 1;
        if (vkCreateGraphicsPipelines(logicalDevice, VK_NULL_HANDLE,
                                      pipelineCreateInfoCount, &createInfo,
                                      nullptr, &getHandle())
            != VK_SUCCESS)
            io::logging::Logger::trace(std::cout, "Created graphics pipeline",
                                       { "CREATE" });
    }

    void GraphicsPipeline::bind(const VkCommandBuffer &commandBuffer)
    {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                          getHandle());
    }
} // namespace brasio::renderer::vulkan
