#include <renderer/vulkan/compute-pipeline.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    ComputePipeline::ComputePipeline(const LogicalDeviceType &logicalDevice,
                                     const VkComputePipelineCreateInfo &createInfo,
                                     PipelineLayoutType pipelineLayout)
        : Handler("compute pipeline",
                  [&logicalDevice](const VkPipeline &computePipeline) {
                      vkDestroyPipeline(logicalDevice->getHandle(), computePipeline, nullptr);
                  })
        , _pipelineLayout(std::move(pipelineLayout))
    {
        BRASIO_LOG_TRACE("Creating compute pipeline", { "CREATE" });
        BRASIO_VULKAN_CHECK(vkCreateComputePipelines(logicalDevice->getHandle(), nullptr, 1,
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
