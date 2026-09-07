#include <renderer/vulkan/pipeline-layout.hh>

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
        if (vkCreatePipelineLayout(logicalDevice, &createInfo, nullptr,
                                   &getHandle())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL("Could not create pipelineLayout",
                                { "CREATE" });
        }

        BRASIO_LOG_TRACE("Created pipeline layout", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
