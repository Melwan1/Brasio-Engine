#include <renderer/vulkan/camera-uniform.hh>

#include <renderer/vulkan/vulkan-renderer.hh>
#include <renderer/vulkan/builders/all.hh>

namespace brasio::renderer::vulkan
{
    CameraUniform::CameraUniform(const VulkanRenderer &renderer)
    {
        unsigned framesInFlight = renderer.getMaxFramesInFlight();

        _descriptorSetLayout =
            builders::DescriptorSetLayoutBuilder(renderer).withUniformBuffers(1).build();

        VkDeviceSize bufferSize = sizeof(structs::UniformBufferObject);
        for (unsigned frame = 0; frame < framesInFlight; frame++)
        {
            _uniformBuffers.emplace_back(
                builders::UniformBufferBuilder(renderer).withSize(bufferSize).build());
            _uniformBuffers.back()->mapMemory();
        }

        _descriptorPool = builders::DescriptorPoolBuilder(renderer)
                              .withDescriptorPoolSizes(
                                  { builders::DescriptorPoolSizeBuilder()
                                        .withDescriptorCount(framesInFlight)
                                        .withDescriptorType(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
                                        .build() })
                              .withMaxSets(framesInFlight)
                              .build();

        _descriptorSets = builders::DescriptorSetsBuilder(renderer, _descriptorPool->getHandle())
                              .withSetsCount(framesInFlight)
                              .withSetLayout(_descriptorSetLayout->getHandle())
                              .build();

        _descriptorSets->update(_uniformBuffers, std::vector<const Texture *>{}, {});
    }

    void CameraUniform::setContent(uint32_t frame, structs::UniformBufferObject ubo)
    {
        _uniformBuffers.at(frame)->setContent(&ubo);
    }

    void CameraUniform::bind(const VkCommandBuffer &commandBuffer,
                             const VkPipelineLayout &pipelineLayout, uint32_t frame) const
    {
        vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0,
                                1, &_descriptorSets->getHandle().at(frame), 0, nullptr);
    }
} // namespace brasio::renderer::vulkan
