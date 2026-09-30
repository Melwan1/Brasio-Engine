#include <renderer/vulkan/compute-pipeline.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    ComputePipeline::ComputePipeline(const VulkanRenderer &renderer,
                                     const VkComputePipelineCreateInfo &createInfo,
                                     PipelineLayoutType pipelineLayout)
        : Handler("compute pipeline",
                  [&renderer](const VkPipeline &computePipeline) {
                      vkDestroyPipeline(renderer.getLogicalDevice(), computePipeline, nullptr);
                  })
        , _renderer(renderer)
        , _pipelineLayout(std::move(pipelineLayout))
    {
        BRASIO_LOG_TRACE("Creating compute pipeline", { "CREATE" });
        BRASIO_VULKAN_CHECK(vkCreateComputePipelines(renderer.getLogicalDevice(), nullptr, 1,
                                                     &createInfo, nullptr, &getHandle()),
                            "create compute pipeline", { "CREATE" });
        BRASIO_LOG_TRACE("Created compute pipeline", { "CREATE" });
    }

    void ComputePipeline::bind(const VkCommandBuffer &commandBuffer) const
    {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, getHandle());
    }

    const PipelineLayout &ComputePipeline::getPipelineLayout() const
    {
        return *_pipelineLayout;
    }
} // namespace brasio::renderer::vulkan
