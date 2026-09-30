#include <renderer/vulkan/pipeline-layout.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    PipelineLayout::PipelineLayout(const VulkanRenderer &renderer,
                                   DescriptorSetLayoutType descriptorSetLayout,
                                   const VkPipelineLayoutCreateInfo &createInfo)
        : Handler("pipeline layout",
                  [&renderer](const VkPipelineLayout &pipelineLayout) {
                      vkDestroyPipelineLayout(renderer.getLogicalDevice(), pipelineLayout, nullptr);
                  })
        , _descriptorSetLayout(std::move(descriptorSetLayout))
    {
        BRASIO_LOG_TRACE("Creating pipeline layout", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreatePipelineLayout(renderer.getLogicalDevice(), &createInfo, nullptr, &getHandle()),
            "pipeline layout", { "CREATE" });
        BRASIO_LOG_TRACE("Created pipeline layout", { "CREATE" });
    }

    const DescriptorSetLayout &PipelineLayout::getDescriptorSetLayout() const
    {
        return *_descriptorSetLayout;
    }
} // namespace brasio::renderer::vulkan
