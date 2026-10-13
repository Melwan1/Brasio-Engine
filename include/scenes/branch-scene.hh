#pragma once

#include <scenes/scene-node.hh>

#include <memory>
#include <vector>

namespace brasio::scenes
{
    class BranchScene : public SceneNode
    {
    public:
        BranchScene(const std::string &id, const SceneRectangle &sceneRectangle,
                    std::vector<SceneNodeType> childScenes);

        virtual void render(const VkCommandBuffer &cmd) override;
        virtual void checkLayout(const SceneRectangle &sceneRectangle) override;

        virtual void emit(YAML::Emitter &out) const override;

    private:
        SceneRectangle _sceneRectangle;
        std::vector<SceneNodeType> _childScenes;
    };

    using BranchSceneType = std::unique_ptr<BranchScene>;
} // namespace brasio::scenes
