#pragma once

#include <vulkan/vulkan_core.h>

#include <memory>

#include <core/handler.hh>
#include <renderer/vulkan/buffer.hh>
#include <renderer/vulkan/texture.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class DescriptorSets : public core::Handler<std::vector<VkDescriptorSet>>
    {
    public:
        DescriptorSets(const VulkanRenderer &renderer,
                       const VkDescriptorSetAllocateInfo &allocateInfo);

        void update(const std::vector<BufferType> &uniformBuffers,
                    const std::vector<TextureType> &textures,
                    const std::vector<BufferType> &storageBuffers);

    private:
        const VulkanRenderer &_renderer;
    };

    using DescriptorSetsType = std::unique_ptr<DescriptorSets>;

} // namespace brasio::renderer::vulkan
