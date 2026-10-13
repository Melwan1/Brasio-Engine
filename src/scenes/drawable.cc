#include <scenes/drawable.hh>

#include <renderer/vulkan/pipeline.hh>
#include <utils/macros.hh>

namespace brasio::scenes
{
    void Drawable::pushTransform(const VkCommandBuffer &commandBuffer) const
    {
        const VkPipelineLayout &pipelineLayout =
            material->getPipeline()->getPipelineLayout().getHandle();
        vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0,
                           sizeof(glm::mat4), &matrix);
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, const Drawable &drawable)
    {
        out << YAML::BeginMap << BRASIO_YAML_KV(model, *(drawable.model))
            << BRASIO_YAML_KV(material, *(drawable.material))
            << BRASIO_YAML_KV(transform, drawable.transform) << YAML::EndMap;
        return out;
    }
} // namespace brasio::scenes
