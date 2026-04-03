#include <renderer/vulkan/descriptor-pool.hh>

namespace brasio::renderer::vulkan
{

    DescriptorPool::DescriptorPool(const VkDevice &logicalDevice,
                                   const VkDescriptorPoolCreateInfo &createInfo)
        : Handler("descriptor pool",
                  [logicalDevice](const VkDescriptorPool &descriptorPool) {
                      vkDestroyDescriptorPool(logicalDevice, descriptorPool,
                                              nullptr);
                  })
    {
        BRASIO_LOG_TRACE(std::cout, "Creating descriptor pool", { "CREATE" });
        if (vkCreateDescriptorPool(logicalDevice, &createInfo, nullptr,
                                   &getHandle())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL(std::cout, "Could not create descriptor pool",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE(std::cout, "Created descriptor pool", { "CREATE" });
    }

} // namespace brasio::renderer::vulkan
