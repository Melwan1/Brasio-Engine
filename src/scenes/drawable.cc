#include <scenes/drawable.hh>

#include <renderer/structs/push-constants.hh>
#include <renderer/vulkan/pipeline.hh>
#include <scenes/text-label.hh>
#include <utils/macros.hh>

namespace brasio::scenes
{
    void Drawable::pushTransform(const VkCommandBuffer &commandBuffer) const
    {
        const VkPipelineLayout &pipelineLayout =
            material->getPipeline()->getPipelineLayout().getHandle();
        renderer::structs::PushConstants pushConstants{ matrix, glm::vec4(1.0f) };
        vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0,
                           sizeof(pushConstants), &pushConstants);
    }

    void Drawable::pushText(const VkCommandBuffer &commandBuffer,
                            const glm::vec2 &boxPixelSize) const
    {
        const VkPipelineLayout &pipelineLayout =
            textLabel->getMaterial()->getPipeline()->getPipelineLayout().getHandle();
        renderer::structs::PushConstants pushConstants{ textLabel->textMatrix(matrix, boxPixelSize),
                                                        textLabel->getColor() };
        vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0,
                           sizeof(pushConstants), &pushConstants);
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, const Drawable &drawable)
    {
        out << YAML::BeginMap << BRASIO_YAML_KV(model, *(drawable.model));
        if (drawable.material)
        {
            out << BRASIO_YAML_KV(material, *(drawable.material));
        }
        if (drawable.textLabel)
        {
            out << BRASIO_YAML_KV(text, *(drawable.textLabel));
        }
        out << BRASIO_YAML_KV(transform, drawable.transform) << YAML::EndMap;
        return out;
    }
} // namespace brasio::scenes
