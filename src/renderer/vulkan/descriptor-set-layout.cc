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
        io::logging::Logger::trace(std::cout, "Creating descriptor set layout",
                                   { "CREATE" });
        if (vkCreateDescriptorSetLayout(device, &createInfo, nullptr,
                                        &getHandle())
            != VK_SUCCESS)
        {
            io::logging::Logger::critical(
                std::cout, "Could not create descriptor set layout",
                { "CREATE" });
        }
        io::logging::Logger::trace(std::cout, "Created descriptor set layout",
                                   { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
