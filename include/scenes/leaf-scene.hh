#pragma once

#include <scenes/scene-node.hh>
#include <scenes/drawable.hh>
#include <scenes/draw-target.hh>

#include <memory>
#include <vector>

namespace brasio::scenes
{
    class LeafScene : public SceneNode
    {
    public:
        LeafScene(const SceneRectangle &sceneRectangle, DrawTarget drawTarget,
                  std::vector<Drawable> drawables);

        virtual void render(const VkCommandBuffer &commandBuffer) override;
        virtual void checkLayout(const SceneRectangle &sceneRectangle) override;

    private:
        SceneRectangle _sceneRectangle;
        const DrawTarget _drawTarget;
        std::vector<Drawable> _drawables;
    };

    using LeafSceneType = std::unique_ptr<LeafScene>;
} // namespace brasio::scenes
