#include <renderer/vulkan/compute-pipeline.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    ComputePipeline::ComputePipeline(const VulkanRenderer &renderer,
                                     const VkComputePipelineCreateInfo &createInfo,
                                     PipelineLayoutType pipelineLayout)
        : Pipeline(renderer, std::move(pipelineLayout))
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

} // namespace brasio::renderer::vulkan
