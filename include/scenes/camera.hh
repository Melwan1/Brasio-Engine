#pragma once

#include <scenes/scene-rectangle.hh>

#include <glm/glm.hpp>

#include <memory>

#include <yaml-cpp/yaml.h>

namespace brasio::scenes
{
    class Camera
    {
    public:
        Camera(const glm::vec3 &eye, const glm::vec3 &lookAt, const glm::vec3 &up);

        virtual ~Camera() = default;

        const glm::mat4 &getView();
        const glm::mat4 &getProj();

        void buildView();
        virtual void buildProj() = 0;

        virtual void resize(const SceneRectangle &sceneRectangle) = 0;

        virtual void emit(YAML::Emitter &out) const = 0;
        void emitBase(YAML::Emitter &out) const;

    protected:
        glm::vec3 _eye;
        glm::vec3 _lookAt;
        glm::vec3 _up;

        glm::mat4 _view;
        glm::mat4 _proj;
    };

    YAML::Emitter &operator<<(YAML::Emitter &out, const Camera &camera);

    using CameraType = std::unique_ptr<Camera>;

} // namespace brasio::scenes
