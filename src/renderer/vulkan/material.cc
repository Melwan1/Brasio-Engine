#include <renderer/vulkan/material.hh>
#include <renderer/vulkan/builders/descriptor-pool-builder.hh>
#include <renderer/vulkan/builders/descriptor-pool-size-builder.hh>
#include <renderer/vulkan/builders/descriptor-sets-builder.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::renderer::vulkan
{
    Material::Material(const VulkanRenderer &renderer, const Pipeline *pipeline,
                       const Texture *texture)
        : _renderer(renderer)
        , _pipeline(pipeline)
        , _texture(texture)
        , _descriptorPool{}
        , _descriptorSets{}
    {
        if (texture == nullptr)
        {
            return;
        }
        unsigned framesInFlight = renderer.getMaxFramesInFlight();
        _descriptorPool =
            builders::DescriptorPoolBuilder(renderer)
                .withDescriptorPoolSizes(
                    { builders::DescriptorPoolSizeBuilder()
                          .withDescriptorCount(framesInFlight)
                          .withDescriptorType(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
                          .build(),
                      builders::DescriptorPoolSizeBuilder()
                          .withDescriptorCount(framesInFlight)
                          .withDescriptorType(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
                          .build() })
                .withMaxSets(framesInFlight)
                .build();

        _descriptorSets =
            builders::DescriptorSetsBuilder(renderer, _descriptorPool->getHandle())
                .withSetsCount(framesInFlight)
                .withSetLayout(_pipeline->getPipelineLayout().getDescriptorSetLayout().getHandle())
                .build();

        _descriptorSets->update(renderer.getUniformBuffers(), { _texture }, {});
    }

    void Material::bind(const VkCommandBuffer &commandBuffer) const
    {
        _pipeline->bind(commandBuffer);
        if (_descriptorSets)
        {
            vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                                    _pipeline->getPipelineLayout().getHandle(), 0, 1,
                                    &_descriptorSets->getHandle().at(_renderer.getCurrentFrame()),
                                    0, nullptr);
        }
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
