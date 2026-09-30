#include <renderer/vulkan/descriptor-set-layout.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{

    DescriptorSetLayout::DescriptorSetLayout(const VulkanRenderer &renderer,
                                             const VkDescriptorSetLayoutCreateInfo &createInfo)
        : Handler("descriptor set layout",
                  [&renderer](const VkDescriptorSetLayout &descriptorSetLayout) {
                      vkDestroyDescriptorSetLayout(renderer.getLogicalDevice(), descriptorSetLayout,
                                                   nullptr);
                  })
    {
        BRASIO_LOG_TRACE("Creating descriptor set layout", { "CREATE" });
        BRASIO_VULKAN_CHECK(vkCreateDescriptorSetLayout(renderer.getLogicalDevice(), &createInfo,
                                                        nullptr, &getHandle()),
                            "create descriptor set layout", { "CREATE" });
        BRASIO_LOG_TRACE("Created descriptor set layout", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
