#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

namespace brasio::renderer::vulkan
{
    class Buffer;
    class ImageAttachment;
    class VulkanRenderer;

    class Memory : public core::Handler<VkDeviceMemory>
    {
    public:
        Memory(const VulkanRenderer &renderer, const Buffer &buffer,
               VkMemoryPropertyFlags memoryProperties, void *data, size_t size);

        Memory(const VulkanRenderer &renderer, const ImageAttachment &imageAttachment,
               VkMemoryPropertyFlags memoryProperties);

        void allocate(const VkMemoryPropertyFlags &memoryProperties,
                      const VkMemoryRequirements &memoryRequirements);

        void map();
        void unmap();
        void setContent(const void *content);

    private:
        const VulkanRenderer &_renderer;
        size_t _size;
        void *_deviceData;
    };

    using MemoryType = std::unique_ptr<Memory>;
} // namespace brasio::renderer::vulkan
