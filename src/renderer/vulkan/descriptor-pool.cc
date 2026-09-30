#include <renderer/vulkan/descriptor-pool.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{

    DescriptorPool::DescriptorPool(const VulkanRenderer &renderer,
                                   const VkDescriptorPoolCreateInfo &createInfo)
        : Handler("descriptor pool", [&renderer](const VkDescriptorPool &descriptorPool) {
            vkDestroyDescriptorPool(renderer.getLogicalDevice(), descriptorPool, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating descriptor pool", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreateDescriptorPool(renderer.getLogicalDevice(), &createInfo, nullptr, &getHandle()),
            "create descriptor pool", { "CREATE" });
        BRASIO_LOG_TRACE("Created descriptor pool", { "CREATE" });
    }

    void DescriptorPool::setDescriptorSets(DescriptorSetsType descriptorSets)
    {
        _descriptorSets = std::move(descriptorSets);
    }

    const DescriptorSets &DescriptorPool::getDescriptorSets() const
    {
        return *_descriptorSets;
    }

} // namespace brasio::renderer::vulkan
