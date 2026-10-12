#include <scenes/leaf-scene.hh>

#include <utility>

namespace brasio::scenes
{
    LeafScene::LeafScene(const SceneRectangle &sceneRectangle, DrawTarget drawTarget,
                         std::vector<Drawable> drawables)
        : _sceneRectangle(sceneRectangle)
        , _drawTarget(drawTarget)
        , _drawables(std::move(drawables))
    {}

    void LeafScene::render(const VkCommandBuffer &commandBuffer)
    {
        VkViewport viewport{};
        viewport.x = static_cast<float>(_sceneRectangle.left);
        viewport.y = static_cast<float>(_sceneRectangle.top);
        viewport.width = static_cast<float>(_sceneRectangle.width);
        viewport.height = static_cast<float>(_sceneRectangle.height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = { static_cast<int32_t>(_sceneRectangle.left),
                           static_cast<int32_t>(_sceneRectangle.top) };
        scissor.extent = { _sceneRectangle.width, _sceneRectangle.height };
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

        for (const Drawable &drawable : _drawables)
        {
            drawable.material->bind(commandBuffer);
            drawable.pushTransform(commandBuffer);
            drawable.mesh->draw(commandBuffer);
        }
    }

    void LeafScene::checkLayout(const SceneRectangle &sceneRectangle)
    {
        _sceneRectangle = sceneRectangle;
    }

} // namespace brasio::scenes
