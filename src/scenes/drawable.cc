#include <scenes/drawable.hh>

#include <renderer/vulkan/pipeline.hh>

namespace brasio::scenes
{
    void Drawable::pushTransform(const VkCommandBuffer &commandBuffer) const
    {
        const VkPipelineLayout &pipelineLayout =
            material->getPipeline()->getPipelineLayout().getHandle();
        vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0,
                           sizeof(glm::mat4), &transform);
    }
} // namespace brasio::scenes
