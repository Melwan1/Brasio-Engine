#include <renderer/vulkan/fence.hh>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan
{
    Fence::Fence(const VkDevice &logicalDevice,
                 const VkFenceCreateInfo &createInfo)
        : Handler("fence", [logicalDevice](const VkFence &fence) {
            vkDestroyFence(logicalDevice, fence, nullptr);
        })
    {
        io::logging::Logger::trace(std::cout, "Creating fence", { "CREATE" });
        if (vkCreateFence(logicalDevice, &createInfo, nullptr, &getHandle())
            != VK_SUCCESS)
        {
            io::logging::Logger::critical(std::cout, "Could not create fence",
                                          { "CREATE" });
        }
        io::logging::Logger::trace(std::cout, "Created fence", { "CREATE" });
    }
} // namespace brasio::renderer::vulkan
