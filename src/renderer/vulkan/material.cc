#include <renderer/vulkan/material.hh>

namespace brasio::renderer::vulkan
{
    Material::Material(const VulkanRenderer &renderer, const Pipeline *pipeline,
                       const Texture *texture)
        : _renderer(renderer)
        , _pipeline(pipeline)
        , _texture(texture)
    {}

    void Material::bind(const VkCommandBuffer &commandBuffer) const
    {
        _pipeline->bind(commandBuffer);
    }

    const Pipeline *Material::getPipeline() const
    {
        return _pipeline;
    }

    const Texture *Material::getTexture() const
    {
        return _texture;
    }
} // namespace brasio::renderer::vulkan
