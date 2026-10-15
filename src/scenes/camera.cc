#include <scenes/camera.hh>

#include <glm/gtc/matrix_transform.hpp>

#include <utils/macros.hh>

namespace brasio::scenes
{
    Camera::Camera(const glm::vec3 &eye, const glm::vec3 &lookAt, const glm::vec3 &up)
        : _eye(eye)
        , _lookAt(lookAt)
        , _up(up)
    {
        buildView();
    }

    void Camera::buildView()
    {
        _view = glm::lookAt(_eye, _lookAt, _up);
    }

    const glm::mat4 &Camera::getView()
    {
        return _view;
    }

    const glm::mat4 &Camera::getProj()
    {
        return _proj;
    }

    void Camera::emitBase(YAML::Emitter &out) const
    {
        std::vector<float> eyeVector = { _eye[0], _eye[1], _eye[2] };
        std::vector<float> lookAtVector = { _lookAt[0], _lookAt[1], _lookAt[2] };
        std::vector<float> upVector = { _up[0], _up[1], _up[2] };
        out << BRASIO_YAML_KV(eye, YAML::Flow << eyeVector)
            << BRASIO_YAML_KV(look_at, YAML::Flow << lookAtVector)
            << BRASIO_YAML_KV(up, YAML::Flow << upVector);
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, const Camera &camera)
    {
        camera.emit(out);
        return out;
    }

} // namespace brasio::scenes
