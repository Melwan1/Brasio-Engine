#include <renderer/vulkan/material.hh>
#include <renderer/vulkan/builders/descriptor-pool-builder.hh>
#include <renderer/vulkan/builders/descriptor-pool-size-builder.hh>
#include <renderer/vulkan/builders/descriptor-sets-builder.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::renderer::vulkan
{
    Material::Material(const std::string &id, const VulkanRenderer &renderer,
                       const Pipeline *pipeline, const Texture *texture)
        : _id(id)
        , _renderer(renderer)
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
                          .withDescriptorType(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
                          .build() })
                .withMaxSets(framesInFlight)
                .build();

        _descriptorSets =
            builders::DescriptorSetsBuilder(renderer, _descriptorPool->getHandle())
                .withSetsCount(framesInFlight)
                .withSetLayout(_pipeline->getPipelineLayout().getDescriptorSetLayout(1).getHandle())
                .build();

        _descriptorSets->update({}, { _texture }, {});
        _dirtyFrames.assign(framesInFlight, false);
    }

    const std::string &Material::getId() const
    {
        return _id;
    }

    void Material::setTexture(const Texture *texture)
    {
        _texture = texture;
        if (_descriptorSets)
        {
            _dirtyFrames.assign(_renderer.getMaxFramesInFlight(), true);
        }
    }

    void Material::bind(const VkCommandBuffer &commandBuffer) const
    {
        _pipeline->bind(commandBuffer);
        if (_descriptorSets)
        {
            uint32_t frame = _renderer.getCurrentFrame();
            if (!_dirtyFrames.empty() && _dirtyFrames[frame])
            {
                _descriptorSets->updateTexture(frame, _texture);
                _dirtyFrames[frame] = false;
            }
            vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                                    _pipeline->getPipelineLayout().getHandle(), 1, 1,
                                    &_descriptorSets->getHandle().at(frame), 0, nullptr);
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

    YAML::Emitter &operator<<(YAML::Emitter &out, const Material &material)
    {
        out << material.getId();
        return out;
    }
} // namespace brasio::renderer::vulkan
