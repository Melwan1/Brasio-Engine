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
        io::logging::Logger::trace(std::cout, "Creating descriptor pool",
                                   { "CREATE" });
        if (vkCreateDescriptorPool(logicalDevice, &createInfo, nullptr,
                                   &getHandle())
            != VK_SUCCESS)
        {
            io::logging::Logger::critical(
                std::cout, "Could not create descriptor pool", { "CREATE" });
        }
        io::logging::Logger::trace(std::cout, "Created descriptor pool",
                                   { "CREATE" });
    }

} // namespace brasio::renderer::vulkan
