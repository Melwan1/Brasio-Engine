#include <renderer/vulkan/descriptor-set-layout.hh>
#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan
{

    DescriptorSetLayout::DescriptorSetLayout(
        const VkDevice &device,
        const VkDescriptorSetLayoutCreateInfo &createInfo)
        : Handler("descriptor set layout",
                  [device](const VkDescriptorSetLayout &descriptorSetLayout) {
                      vkDestroyDescriptorSetLayout(device, descriptorSetLayout,
                                                   nullptr);
                  })
    {
        BRASIO_LOG_TRACE("Creating descriptor set layout",
                         { "CREATE" });
        if (vkCreateDescriptorSetLayout(device, &createInfo, nullptr,
                                        &getHandle())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL(
                                "Could not create descriptor set layout",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE("Created descriptor set layout",
                         { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
