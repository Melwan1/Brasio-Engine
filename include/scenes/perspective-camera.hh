#pragma once

#include <scenes/camera.hh>

namespace brasio::scenes
{
    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(const glm::vec3 &eye, const glm::vec3 &lookAt, const glm::vec3 &up,
                          float fovY, unsigned screenWidth, unsigned screenHeight,
                          float zNear = 0.1f, float zFar = 100.0f);

        virtual void buildProj() override;

        virtual void resize(const SceneRectangle &sceneRectangle) override;

        virtual void emit(YAML::Emitter &out) const override;

        float getFov() const;
        unsigned getScreenWidth() const;
        unsigned getScreenHeight() const;
        float getZNear() const;
        float getZFar() const;

    private:
        float _fovY;
        unsigned _screenWidth;
        unsigned _screenHeight;
        float _zNear;
        float _zFar;
    };
} // namespace brasio::scenes
