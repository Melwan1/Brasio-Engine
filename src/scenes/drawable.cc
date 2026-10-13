#include <scenes/drawable.hh>

#include <renderer/vulkan/pipeline.hh>
#include <utils/macros.hh>

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace brasio::scenes
{
    void Drawable::pushTransform(const VkCommandBuffer &commandBuffer) const
    {
        const VkPipelineLayout &pipelineLayout =
            material->getPipeline()->getPipelineLayout().getHandle();
        vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0,
                           sizeof(glm::mat4), &transform);
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, const Drawable &drawable)
    {
        out << YAML::BeginMap << BRASIO_YAML_KV(model, *(drawable.model))
            << BRASIO_YAML_KV(material, *(drawable.material));
        if (drawable.transform == glm::mat4(1.0f))
        {
            out << BRASIO_YAML_KV(transform, "identity");
        }
        else
        {
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::decompose(drawable.transform, scale, rotation, translation, skew, perspective);
            (void)skew;
            (void)perspective;

            glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
            float yaw, pitch, roll;
            glm::extractEulerAngleYXZ(rotationMatrix, yaw, pitch, roll);
            glm::vec3 rotationDegrees = glm::degrees(glm::vec3(yaw, pitch, roll));

            out << YAML::Key << "transform";
            out << YAML::BeginMap;
            std::vector<float> translateVector = { translation[0], translation[1], translation[2] };
            std::vector<float> rotateVector = { rotationDegrees[0], rotationDegrees[1],
                                                rotationDegrees[2] };
            std::vector<float> scaleVector = { scale[0], scale[1], scale[2] };
            out << BRASIO_YAML_KV(translation, YAML::Flow << translateVector)
                << BRASIO_YAML_KV(rotation, YAML::Flow << rotateVector)
                << BRASIO_YAML_KV(scale, YAML::Flow << scaleVector) << YAML::EndMap << YAML::EndMap;
        }
        return out;
    }
} // namespace brasio::scenes
