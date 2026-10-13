#include <scenes/scene-rectangle.hh>
#include <utils/macros.hh>

namespace brasio::scenes
{
    YAML::Emitter &operator<<(YAML::Emitter &out, const SceneRectangle &sceneRectangle)
    {
        const auto &[top, left, width, height] = sceneRectangle;
        out << YAML::BeginMap << BRASIO_YAML_ATTRIBUTE(top) << BRASIO_YAML_ATTRIBUTE(left)
            << BRASIO_YAML_ATTRIBUTE(width) << BRASIO_YAML_ATTRIBUTE(height) << YAML::EndMap;
        return out;
    }
} // namespace brasio::scenes
