#pragma once

#include <memory>

#include <renderer/vulkan/pipeline.hh>
#include <renderer/vulkan/texture.hh>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class Material
    {
    public:
        Material(const VulkanRenderer &renderer, const Pipeline *pipeline, const Texture *texture);

        void bind(const VkCommandBuffer &commandBuffer) const;

        const Pipeline *getPipeline() const;
        const Texture *getTexture() const;

    private:
        const VulkanRenderer &_renderer;
        const Pipeline *_pipeline;
        const Texture *_texture;
    };

    using MaterialType = std::unique_ptr<Material>;
} // namespace brasio::renderer::vulkan
