#pragma once

#include <scenes/scene-node.hh>
#include <scenes/drawable.hh>
#include <scenes/draw-target.hh>
#include <scenes/camera.hh>
#include <scenes/text-label.hh>

#include <renderer/vulkan/vulkan-renderer.hh>
#include <renderer/vulkan/camera-uniform.hh>

#include <memory>
#include <vector>

namespace brasio::scenes
{
    class LeafScene : public SceneNode
    {
    public:
        LeafScene(const std::string &id, const SceneRectangle &sceneRectangle,
                  DrawTarget drawTarget, std::vector<Drawable> drawables,
                  std::vector<TextLabelType> textLabels, CameraType camera,
                  const renderer::vulkan::VulkanRenderer &renderer);

        virtual void render(const VkCommandBuffer &commandBuffer) override;
        virtual void checkLayout(const SceneRectangle &sceneRectangle) override;

        virtual TextLabel *findText(const std::string &id) override;

        virtual void emit(YAML::Emitter &out) const override;

    private:
        SceneRectangle _relativeRectangle;
        SceneRectangle _sceneRectangle;
        const DrawTarget _drawTarget;
        std::vector<Drawable> _drawables;
        std::vector<TextLabelType> _textLabels;
        CameraType _camera;
        const renderer::vulkan::VulkanRenderer &_renderer;
        renderer::vulkan::CameraUniformType _cameraUniform;
    };

    using LeafSceneType = std::unique_ptr<LeafScene>;
} // namespace brasio::scenes
