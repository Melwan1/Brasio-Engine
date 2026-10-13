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

    YAML::Emitter &operator<<(YAML::Emitter &out, const SceneNode &node)
    {
        node.emit(out);
        return out;
    }

} // namespace brasio::scenes
