#pragma once

#include <scenes/camera.hh>

namespace brasio::scenes
{
    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(const glm::vec3 &eye, const glm::vec3 &lookAt, const glm::vec3 &up,
                           float left, float right, float bottom, float top, float zNear = 0.0f,
                           float zFar = 100.0f);
        virtual void buildProj() override;

        virtual void resize(const SceneRectangle &sceneRectangle) override;

        virtual void emit(YAML::Emitter &out) const override;

        float getLeft() const;
        float getRight() const;
        float getBottom() const;
        float getTop() const;
        float getZNear() const;
        float getZFar() const;

    private:
        float _left;
        float _right;
        float _bottom;
        float _top;
        float _zNear;
        float _zFar;
    };
} // namespace brasio::scenes
