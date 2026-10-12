#include <scenes/branch-scene.hh>

#include <utility>

namespace brasio::scenes
{
    BranchScene::BranchScene(const SceneRectangle &sceneRectangle,
                             std::vector<SceneNodeType> childScenes)
        : _sceneRectangle(sceneRectangle)
        , _childScenes(std::move(childScenes))
    {}

    void BranchScene::render(const VkCommandBuffer &commandBuffer)
    {
        for (SceneNodeType &scene : _childScenes)
        {
            scene->render(commandBuffer);
        }
    }

    void BranchScene::checkLayout(const SceneRectangle &sceneRectangle)
    {
        _sceneRectangle = sceneRectangle;
        for (SceneNodeType &scene : _childScenes)
        {
            scene->checkLayout(_sceneRectangle);
        }
    }

} // namespace brasio::scenes
