#include <scenes/orthographic-camera.hh>

#include <glm/gtc/matrix_transform.hpp>

#include <utils/macros.hh>

namespace brasio::scenes
{
    OrthographicCamera::OrthographicCamera(const glm::vec3 &eye, const glm::vec3 &lookAt,
                                           const glm::vec3 &up, float left, float right,
                                           float bottom, float top, float zNear, float zFar)
        : Camera(eye, lookAt, up)
        , _left(left)
        , _right(right)
        , _bottom(bottom)
        , _top(top)
        , _zNear(zNear)
        , _zFar(zFar)
    {}

    void OrthographicCamera::buildProj()
    {
        _proj = glm::ortho(_left, _right, _bottom, _top, _zNear, _zFar);
    }

    void OrthographicCamera::resize(const SceneRectangle &sceneRectangle)
    {
        _left = static_cast<float>(sceneRectangle.left);
        _right = static_cast<float>(sceneRectangle.left + sceneRectangle.width);
        _top = static_cast<float>(sceneRectangle.top);
        _bottom = static_cast<float>(sceneRectangle.top + sceneRectangle.height);
        buildProj();
    }

    float OrthographicCamera::getLeft() const
    {
        return _left;
    }

    float OrthographicCamera::getRight() const
    {
        return _right;
    }

    float OrthographicCamera::getBottom() const
    {
        return _bottom;
    }

    float OrthographicCamera::getTop() const
    {
        return _top;
    }

    float OrthographicCamera::getZNear() const
    {
        return _zNear;
    }

    float OrthographicCamera::getZFar() const
    {
        return _zFar;
    }

    void OrthographicCamera::emit(YAML::Emitter &out) const
    {
        out << YAML::BeginMap << BRASIO_YAML_KV(type, "ORTHOGRAPHIC");
        emitBase(out);
        out << BRASIO_YAML_KV(left, getLeft()) << BRASIO_YAML_KV(right, getRight())
            << BRASIO_YAML_KV(bottom, getBottom()) << BRASIO_YAML_KV(top, getTop())
            << BRASIO_YAML_KV(near, getZNear()) << BRASIO_YAML_KV(far, getZFar()) << YAML::EndMap;
    }
} // namespace brasio::scenes
