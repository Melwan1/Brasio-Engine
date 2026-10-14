#pragma once

#include <renderer/vulkan/descriptor-set-layout.hh>
#include <renderer/vulkan/descriptor-pool.hh>
#include <renderer/vulkan/descriptor-sets.hh>
#include <renderer/vulkan/buffer.hh>
#include <renderer/structs/uniform-buffer-object.hh>

#include <vulkan/vulkan_core.h>

#include <memory>
#include <vector>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    /**
     * The GPU-side camera uniform of a leaf scene (descriptor set 0).
     *
     * Owns a per-frame uniform buffer holding the view and projection matrices,
     * along with its own descriptor set layout, pool and descriptor sets. Each
     * leaf scene owns one, writes its camera into the current frame's buffer and
     * binds it as set 0 before drawing. The layout is structurally identical to
     * the set 0 declared by graphics pipelines, which makes the descriptor set
     * binding-compatible with any of them.
     */
    class CameraUniform
    {
    public:
        CameraUniform(const VulkanRenderer &renderer);

        void setContent(uint32_t frame, structs::UniformBufferObject ubo);
        void bind(const VkCommandBuffer &commandBuffer, const VkPipelineLayout &pipelineLayout,
                  uint32_t frame) const;

    private:
        DescriptorSetLayoutType _descriptorSetLayout;
        std::vector<BufferType> _uniformBuffers;
        DescriptorPoolType _descriptorPool;
        DescriptorSetsType _descriptorSets;
    };

    using CameraUniformType = std::unique_ptr<CameraUniform>;
} // namespace brasio::renderer::vulkan
