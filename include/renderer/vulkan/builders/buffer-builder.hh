#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/buffer.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;
}

namespace brasio::renderer::vulkan::builders
{

    template <VkBufferUsageFlags usage, VkMemoryPropertyFlags memoryProperties>
    class BufferBuilder : public core::Builder<BufferType>
    {
    public:
        BufferBuilder(const VulkanRenderer &renderer);

        virtual BufferBuilder &base() override;
        virtual BufferType build() override;

        BufferBuilder &withSize(uint32_t size);
        BufferBuilder &withSharingMode(const VkSharingMode &sharingMode);

        BufferBuilder &withData(void *data);

    private:
        const VulkanRenderer &_renderer;
        VkStructureType _structureType;

        uint32_t _size;
        VkSharingMode _sharingMode;

        void *_data;
    };

    using IndexBufferBuilder =
        BufferBuilder<VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT>;
    using StagingBufferBuilder =
        BufferBuilder<VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT>;
    using StorageBufferBuilder =
        BufferBuilder<VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT
                          | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT>;
    using UniformBufferBuilder =
        BufferBuilder<VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT>;
    using VertexBufferBuilder =
        BufferBuilder<VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT>;
} // namespace brasio::renderer::vulkan::builders

#include <renderer/vulkan/builders/buffer-builder.hxx>
