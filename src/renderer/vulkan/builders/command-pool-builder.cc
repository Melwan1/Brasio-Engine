#include <renderer/vulkan/builders/command-pool-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    CommandPoolBuilder::CommandPoolBuilder(const VkDevice &logicalDevice)
        : _logicalDevice(logicalDevice)
    {
        base();
    }

    CommandPoolBuilder &CommandPoolBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        _resetFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        return withQueueFamilyIndex(-1); // should not stay at -1
    }

    CommandPoolBuilder &
    CommandPoolBuilder::withQueueFamilyIndex(uint32_t queueFamilyIndex)
    {
        _queueFamilyIndex = queueFamilyIndex;
        return *this;
    }

    CommandPoolType CommandPoolBuilder::build()
    {
        VkCommandPoolCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.queueFamilyIndex = _queueFamilyIndex;
        createInfo.flags = _resetFlags;

        return std::make_unique<CommandPool>(_logicalDevice, createInfo);
    }
} // namespace brasio::renderer::vulkan::builders
