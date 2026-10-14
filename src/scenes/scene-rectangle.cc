#include <scenes/scene-rectangle.hh>
#include <utils/macros.hh>

namespace brasio::scenes
{
    SceneRectangle SceneRectangle::absoluteIn(const SceneRectangle &parent) const
    {
        return { parent.top + top * parent.height, parent.left + left * parent.width,
                 width * parent.width, height * parent.height };
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, const SceneRectangle &sceneRectangle)
    {
        const auto &[top, left, width, height] = sceneRectangle;
        out << YAML::BeginMap << BRASIO_YAML_ATTRIBUTE(top) << BRASIO_YAML_ATTRIBUTE(left)
            << BRASIO_YAML_ATTRIBUTE(width) << BRASIO_YAML_ATTRIBUTE(height) << YAML::EndMap;
        return out;
    }
} // namespace brasio::scenes
