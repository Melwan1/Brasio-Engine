#include <renderer/vulkan/fence.hh>

#include <io/logging/logger.hh>

Fence::Fence(const VkDevice &logicalDevice, const VkFenceCreateInfo &createInfo)
    : _logicalDevice(logicalDevice)
{
    Logger::trace(std::cout, "Creating fence", { "CREATE" });
    if (vkCreateFence(_logicalDevice, &createInfo, nullptr, &_fence)
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create fence", { "CREATE" });
    }
    Logger::trace(std::cout, "Created fence", { "CREATE" });
}

Fence::~Fence()
{
    Logger::trace(std::cout, "Destroying fence", { "DESTROY" });
    vkDestroyFence(_logicalDevice, _fence, nullptr);
    Logger::trace(std::cout, "Destroyed fence", { "DESTROY" });
}

const VkFence &Fence::getHandle() const
{
    return _fence;
}

VkFence &Fence::getHandle()
{
    return _fence;
}
