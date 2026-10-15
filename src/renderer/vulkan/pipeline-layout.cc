#include <renderer/vulkan/pipeline-layout.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    PipelineLayout::PipelineLayout(const VulkanRenderer &renderer,
                                   std::vector<DescriptorSetLayoutType> descriptorSetLayouts,
                                   const VkPipelineLayoutCreateInfo &createInfo)
        : Handler("pipeline layout",
                  [&renderer](const VkPipelineLayout &pipelineLayout) {
                      vkDestroyPipelineLayout(renderer.getLogicalDevice(), pipelineLayout, nullptr);
                  })
        , _descriptorSetLayouts(std::move(descriptorSetLayouts))
    {
        BRASIO_LOG_TRACE("Creating pipeline layout", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreatePipelineLayout(renderer.getLogicalDevice(), &createInfo, nullptr, &getHandle()),
            "pipeline layout", { "CREATE" });
        BRASIO_LOG_TRACE("Created pipeline layout", { "CREATE" });
    }

    const DescriptorSetLayout &PipelineLayout::getDescriptorSetLayout(size_t index) const
    {
        return *_descriptorSetLayouts.at(index);
    }
} // namespace brasio::renderer::vulkan
