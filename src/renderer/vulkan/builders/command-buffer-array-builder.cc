#include <renderer/vulkan/builders/command-buffer-array-builder.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::renderer::vulkan::builders
{
    CommandBufferArrayBuilder::CommandBufferArrayBuilder(const VulkanRenderer &renderer)
        : _renderer(renderer)
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
    CommandBufferArrayBuilder::withCommandBufferCount(uint32_t commandBufferCount)
    {
        _commandBufferCount = commandBufferCount;
        return *this;
    }

    CommandBufferArrayType CommandBufferArrayBuilder::build()
    {
        VkCommandBufferAllocateInfo allocateInfo{};
        allocateInfo.sType = _structureType;
        allocateInfo.commandBufferCount = _commandBufferCount;
        allocateInfo.commandPool = _renderer.getCommandPool();

        return std::make_unique<CommandBufferArray>(_renderer, allocateInfo);
    }
} // namespace brasio::renderer::vulkan::builders
