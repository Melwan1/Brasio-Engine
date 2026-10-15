#pragma once

#include <vulkan/vulkan_core.h>

#include <memory>

#include <scenes/scene-rectangle.hh>
#include <renderer/renderable.hh>
#include <events/event.hh>

namespace brasio::scenes
{
    class TextLabel;

    class SceneNode : public renderer::Renderable
    {
    public:
        SceneNode(const std::string &id);

        virtual ~SceneNode() = default;

        const std::string &getId() const;

        virtual void render(const VkCommandBuffer &commandBuffer) override = 0;

        void checkLayout(uint32_t width, uint32_t height) override;
        virtual void checkLayout(const SceneRectangle &sceneRectangle) = 0;

        virtual TextLabel *findText(const std::string &id);

        virtual void emit(YAML::Emitter &out) const = 0;

    protected:
        std::string _id;
    };

    YAML::Emitter &operator<<(YAML::Emitter &out, const SceneNode &sceneNode);

    using SceneNodeType = std::unique_ptr<SceneNode>;
} // namespace brasio::scenes
