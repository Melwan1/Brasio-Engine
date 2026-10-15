#include <scenes/branch-scene.hh>
#include <utils/macros.hh>

#include <utility>

namespace brasio::scenes
{
    BranchScene::BranchScene(const std::string &id, const SceneRectangle &sceneRectangle,
                             std::vector<SceneNodeType> childScenes)
        : SceneNode(id)
        , _relativeRectangle(sceneRectangle)
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
        _sceneRectangle = _relativeRectangle.absoluteIn(sceneRectangle);
        for (SceneNodeType &scene : _childScenes)
        {
            scene->checkLayout(_sceneRectangle);
        }
    }

    TextLabel *BranchScene::findText(const std::string &id)
    {
        for (SceneNodeType &scene : _childScenes)
        {
            if (TextLabel *label = scene->findText(id))
            {
                return label;
            }
        }
        return nullptr;
    }

    void BranchScene::emit(YAML::Emitter &out) const
    {
        out << YAML::BeginMap << BRASIO_YAML_KV(id, _id) << BRASIO_YAML_KV(type, "BRANCH")
            << BRASIO_YAML_KV(scene_rectangle, _relativeRectangle);
        out << YAML::Key << "children" << YAML::BeginSeq;
        for (const SceneNodeType &sceneNode : _childScenes)
        {
            out << *sceneNode;
        }
        out << YAML::EndSeq << YAML::EndMap;
    }

} // namespace brasio::scenes
