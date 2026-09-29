#include <renderer/vulkan/pipeline-layout.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    PipelineLayout::PipelineLayout(const VkDevice &logicalDevice,
                                   DescriptorSetLayoutType descriptorSetLayout,
                                   const VkPipelineLayoutCreateInfo &createInfo)
        : Handler("pipeline layout",
                  [logicalDevice](const VkPipelineLayout &pipelineLayout) {
                      vkDestroyPipelineLayout(logicalDevice, pipelineLayout, nullptr);
                  })
        , _descriptorSetLayout(std::move(descriptorSetLayout))
    {
        BRASIO_LOG_TRACE("Creating pipeline layout", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreatePipelineLayout(logicalDevice, &createInfo, nullptr, &getHandle()),
            "pipeline layout", { "CREATE" });
        BRASIO_LOG_TRACE("Created pipeline layout", { "CREATE" });
    }

    const DescriptorSetLayout &PipelineLayout::getDescriptorSetLayout() const
    {
        return *_descriptorSetLayout;
    }
} // namespace brasio::renderer::vulkan
