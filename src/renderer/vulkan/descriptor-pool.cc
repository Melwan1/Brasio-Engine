#include <renderer/vulkan/descriptor-pool.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{

    DescriptorPool::DescriptorPool(const VkDevice &logicalDevice,
                                   const VkDescriptorPoolCreateInfo &createInfo)
        : Handler("descriptor pool", [logicalDevice](const VkDescriptorPool &descriptorPool) {
            vkDestroyDescriptorPool(logicalDevice, descriptorPool, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating descriptor pool", { "CREATE" });
        BRASIO_VULKAN_CHECK(
            vkCreateDescriptorPool(logicalDevice, &createInfo, nullptr, &getHandle()),
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
