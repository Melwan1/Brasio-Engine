#include <scenes/scene-node.hh>

namespace brasio::scenes
{
    SceneNode::SceneNode(const std::string &id)
        : _id(id)
    {}

    const std::string &SceneNode::getId() const
    {
        return _id;
    }

    void SceneNode::checkLayout(uint32_t width, uint32_t height)
    {
        checkLayout(
            SceneRectangle{ 0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height) });
    }

    TextLabel *SceneNode::findText(const std::string &)
    {
        return nullptr;
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, const SceneNode &node)
    {
        node.emit(out);
        return out;
    }

} // namespace brasio::scenes
