#include <renderer/vulkan/builders/command-buffer-array-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    CommandBufferArrayBuilder::CommandBufferArrayBuilder(
        const VkDevice &logicalDevice, const VkCommandPool &commandPool)
        : _logicalDevice(logicalDevice)
        , _commandPool(commandPool)
    {
        base();
    }

    CommandBufferArrayBuilder &CommandBufferArrayBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        return withLevel(VK_COMMAND_BUFFER_LEVEL_PRIMARY);
    }

    CommandBufferArrayBuilder &
    CommandBufferArrayBuilder::withLevel(const VkCommandBufferLevel &level)
    {
        _level = level;
        return *this;
    }

    CommandBufferArrayBuilder &
    CommandBufferArrayBuilder::withCommandBufferCount(
        uint32_t commandBufferCount)
    {
        _commandBufferCount = commandBufferCount;
        return *this;
    }

    CommandBufferArrayType CommandBufferArrayBuilder::build()
    {
        VkCommandBufferAllocateInfo allocateInfo{};
        allocateInfo.sType = _structureType;
        allocateInfo.commandBufferCount = _commandBufferCount;
        allocateInfo.commandPool = _commandPool;

        return std::make_unique<CommandBufferArray>(_logicalDevice,
                                                    allocateInfo);
    }
} // namespace brasio::renderer::vulkan::builders
