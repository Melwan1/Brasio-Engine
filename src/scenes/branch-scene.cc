#include <scenes/branch-scene.hh>
#include <utils/macros.hh>

#include <utility>

namespace brasio::scenes
{
    BranchScene::BranchScene(const std::string &id, const SceneRectangle &sceneRectangle,
                             std::vector<SceneNodeType> childScenes)
        : SceneNode(id)
        , _sceneRectangle(sceneRectangle)
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

    void BranchScene::emit(YAML::Emitter &out) const
    {
        out << YAML::BeginMap << BRASIO_YAML_KV(id, _id) << BRASIO_YAML_KV(type, "BRANCH")
            << BRASIO_YAML_KV(scene_rectangle, _sceneRectangle);
        out << YAML::Key << "children" << YAML::BeginSeq;
        for (const SceneNodeType &sceneNode : _childScenes)
        {
            out << *sceneNode;
        }
        out << YAML::EndSeq << YAML::EndMap;
    }

} // namespace brasio::scenes
