#include <renderer/vulkan/descriptor-set-layout.hh>
#include <io/logging/logger.hh>
#include <utils/libutils.hh>

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
        BRASIO_LOG_TRACE("Creating descriptor set layout", { "CREATE" });
        BRASIO_VULKAN_CHECK(vkCreateDescriptorSetLayout(device, &createInfo,
                                                        nullptr, &getHandle()),
                            "create descriptor set layout", { "CREATE" });
        BRASIO_LOG_TRACE("Created descriptor set layout", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
