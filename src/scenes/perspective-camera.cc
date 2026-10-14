#include <scenes/perspective-camera.hh>

#include <glm/gtc/matrix_transform.hpp>

#include <utils/macros.hh>

namespace brasio::scenes
{
    PerspectiveCamera::PerspectiveCamera(const glm::vec3 &eye, const glm::vec3 &lookAt,
                                         const glm::vec3 &up, float fovY, unsigned screenWidth,
                                         unsigned screenHeight, float zNear, float zFar)
        : Camera(eye, lookAt, up)
        , _fovY(fovY)
        , _screenWidth(screenWidth)
        , _screenHeight(screenHeight)
        , _zNear(zNear)
        , _zFar(zFar)
    {}

    void PerspectiveCamera::buildProj()
    {
        _proj = glm::perspective(_fovY, static_cast<float>(_screenWidth) / _screenHeight, _zNear,
                                 _zFar);
    }

    void PerspectiveCamera::resize(const SceneRectangle &sceneRectangle)
    {
        _screenWidth = sceneRectangle.width;
        _screenHeight = sceneRectangle.height;
        buildProj();
    }

    float PerspectiveCamera::getFov() const
    {
        return _fovY;
    }

    unsigned PerspectiveCamera::getScreenWidth() const
    {
        return _screenWidth;
    }

    unsigned PerspectiveCamera::getScreenHeight() const
    {
        return _screenHeight;
    }

    float PerspectiveCamera::getZNear() const
    {
        return _zNear;
    }

    float PerspectiveCamera::getZFar() const
    {
        return _zFar;
    }

    void PerspectiveCamera::emit(YAML::Emitter &out) const
    {
        out << YAML::BeginMap << BRASIO_YAML_KV(type, "PERSPECTIVE");
        emitBase(out);
        out << BRASIO_YAML_KV(fov, glm::degrees(getFov())) << BRASIO_YAML_KV(near, getZNear())
            << BRASIO_YAML_KV(far, getZFar()) << YAML::EndMap;
    }
} // namespace brasio::scenes
