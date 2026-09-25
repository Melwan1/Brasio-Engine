#include <renderer/vulkan/pipeline-layout.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    PipelineLayout::PipelineLayout(const VkDevice &logicalDevice,
                                   const VkPipelineLayoutCreateInfo &createInfo)
        : Handler("pipeline layout",
                  [logicalDevice](const VkPipelineLayout &pipelineLayout) {
                      vkDestroyPipelineLayout(logicalDevice, pipelineLayout,
                                              nullptr);
                  })
    {
        BRASIO_LOG_TRACE("Creating pipeline layout", { "CREATE" });
        BRASIO_VULKAN_CHECK(vkCreatePipelineLayout(logicalDevice, &createInfo,
                                                   nullptr, &getHandle()),
                            "pipeline layout", { "CREATE" });
        BRASIO_LOG_TRACE("Created pipeline layout", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
