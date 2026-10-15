#include <scenes/leaf-scene.hh>

#include <renderer/structs/uniform-buffer-object.hh>

#include <utility>

namespace brasio::scenes
{
    namespace
    {
        glm::vec2 computeBoxPixelSize(const renderer::structs::UniformBufferObject &ubo,
                                      const glm::mat4 &boxMatrix, const SceneRectangle &rectangle)
        {
            glm::mat4 viewProjection = ubo.proj * ubo.view;
            auto project = [&](const glm::vec4 &localCorner) {
                glm::vec4 clip = viewProjection * boxMatrix * localCorner;
                glm::vec3 ndc = glm::vec3(clip) / clip.w;
                return glm::vec2((ndc.x * 0.5f + 0.5f) * rectangle.width,
                                 (ndc.y * 0.5f + 0.5f) * rectangle.height);
            };
            glm::vec2 corner0 = project({ -0.5f, -0.5f, 0.0f, 1.0f });
            glm::vec2 corner1 = project({ 0.5f, 0.5f, 0.0f, 1.0f });
            return glm::abs(corner1 - corner0);
        }
    } // namespace

    LeafScene::LeafScene(const std::string &id, const SceneRectangle &sceneRectangle,
                         DrawTarget drawTarget, std::vector<Drawable> drawables,
                         std::vector<TextLabelType> textLabels, CameraType camera,
                         const renderer::vulkan::VulkanRenderer &renderer)
        : SceneNode(id)
        , _relativeRectangle(sceneRectangle)
        , _sceneRectangle(sceneRectangle)
        , _drawTarget(drawTarget)
        , _drawables(std::move(drawables))
        , _textLabels(std::move(textLabels))
        , _camera(std::move(camera))
        , _renderer(renderer)
        , _cameraUniform(std::make_unique<renderer::vulkan::CameraUniform>(renderer))
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
        scissor.extent = { static_cast<uint32_t>(_sceneRectangle.width),
                           static_cast<uint32_t>(_sceneRectangle.height) };
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

        uint32_t frame = _renderer.getCurrentFrame();
        renderer::structs::UniformBufferObject ubo{};
        ubo.view = _camera->getView();
        glm::mat4 vulkanClipYFlip(1.0f);
        vulkanClipYFlip[1][1] = -1.0f;
        ubo.proj = vulkanClipYFlip * _camera->getProj();
        _cameraUniform->setContent(frame, ubo);

        for (const Drawable &drawable : _drawables)
        {
            if (drawable.material)
            {
                drawable.material->bind(commandBuffer);
                _cameraUniform->bind(
                    commandBuffer,
                    drawable.material->getPipeline()->getPipelineLayout().getHandle(), frame);
                drawable.pushTransform(commandBuffer);
                drawable.model->mesh().draw(commandBuffer);
            }
            if (drawable.textLabel)
            {
                const renderer::vulkan::Material *textMaterial = drawable.textLabel->getMaterial();
                textMaterial->bind(commandBuffer);
                _cameraUniform->bind(commandBuffer,
                                     textMaterial->getPipeline()->getPipelineLayout().getHandle(),
                                     frame);
                drawable.pushText(commandBuffer,
                                  computeBoxPixelSize(ubo, drawable.matrix, _sceneRectangle));
                drawable.model->mesh().draw(commandBuffer);
            }
        }
    }

    void LeafScene::checkLayout(const SceneRectangle &sceneRectangle)
    {
        _sceneRectangle = _relativeRectangle.absoluteIn(sceneRectangle);
        _camera->resize(_sceneRectangle);
    }

    TextLabel *LeafScene::findText(const std::string &id)
    {
        for (const TextLabelType &label : _textLabels)
        {
            if (label->getId() == id)
            {
                return label.get();
            }
        }
        return nullptr;
    }

    void LeafScene::emit(YAML::Emitter &out) const
    {
        out << YAML::BeginMap << BRASIO_YAML_KV(id, _id) << BRASIO_YAML_KV(type, "LEAF")
            << BRASIO_YAML_KV(target, drawTargetToString(_drawTarget))
            << BRASIO_YAML_KV(scene_rectangle, _relativeRectangle)
            << BRASIO_YAML_KV(camera, *_camera) << BRASIO_YAML_KV(drawables, _drawables)
            << YAML::EndMap;
    }

} // namespace brasio::scenes
