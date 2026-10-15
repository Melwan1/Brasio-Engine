#include <scenes/transform.hh>

#include <utils/macros.hh>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>

namespace brasio::scenes
{
    glm::mat4 Transform::matrix() const
    {
        return glm::translate(glm::mat4(1.0f), translation)
            * glm::mat4_cast(glm::quat(glm::radians(rotation)))
            * glm::scale(glm::mat4(1.0f), scale);
    }

    bool Transform::isIdentity() const
    {
        return translation == glm::vec3(0.0f) && rotation == glm::vec3(0.0f)
            && scale == glm::vec3(1.0f);
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, const Transform &transform)
    {
        if (transform.isIdentity())
        {
            out << "identity";
            return out;
        }
        std::vector<float> translateVector = { transform.translation[0], transform.translation[1],
                                               transform.translation[2] };
        std::vector<float> rotateVector = { transform.rotation[0], transform.rotation[1],
                                            transform.rotation[2] };
        std::vector<float> scaleVector = { transform.scale[0], transform.scale[1],
                                           transform.scale[2] };
        out << YAML::BeginMap << BRASIO_YAML_KV(translation, YAML::Flow << translateVector)
            << BRASIO_YAML_KV(rotation, YAML::Flow << rotateVector)
            << BRASIO_YAML_KV(scale, YAML::Flow << scaleVector) << YAML::EndMap;
        return out;
    }
} // namespace brasio::scenes
