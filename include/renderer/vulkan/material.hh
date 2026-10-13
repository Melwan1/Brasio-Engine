#pragma once

#include <memory>

#include <renderer/vulkan/pipeline.hh>
#include <renderer/vulkan/texture.hh>
#include <renderer/vulkan/descriptor-pool.hh>
#include <renderer/vulkan/descriptor-sets.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class Material
    {
    public:
        Material(const std::string &id, const VulkanRenderer &renderer, const Pipeline *pipeline,
                 const Texture *texture);

        const std::string &getId() const;

        void bind(const VkCommandBuffer &commandBuffer) const;

        const Pipeline *getPipeline() const;
        const Texture *getTexture() const;

    private:
        const std::string _id;
        const VulkanRenderer &_renderer;
        const Pipeline *_pipeline;
        const Texture *_texture;

        DescriptorPoolType _descriptorPool;
        DescriptorSetsType _descriptorSets;
    };

    YAML::Emitter &operator<<(YAML::Emitter &out, const Material &material);

    using MaterialType = std::unique_ptr<Material>;
} // namespace brasio::renderer::vulkan
