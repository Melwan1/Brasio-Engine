#include <scenes/text-label.hh>

#include <fonts/font-manager.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/macros.hh>

#include <glm/gtc/matrix_transform.hpp>

#include <utility>
#include <vector>

namespace brasio::scenes
{
    TextLabel::TextLabel(const std::string &id, const renderer::vulkan::VulkanRenderer &renderer,
                         fonts::FontManager &fontManager,
                         const renderer::vulkan::Pipeline *pipeline, const std::string &font,
                         unsigned fontSize, unsigned maxWidth, const std::string &text,
                         const glm::vec4 &color, HorizontalAlignment horizontalAlignment,
                         VerticalAlignment verticalAlignment)
        : _id(id)
        , _renderer(renderer)
        , _fontManager(fontManager)
        , _font(font)
        , _fontSize(fontSize)
        , _maxWidth(maxWidth)
        , _text(text)
        , _color(color)
        , _horizontalAlignment(horizontalAlignment)
        , _verticalAlignment(verticalAlignment)
        , _texture(_fontManager.loadText(renderer, _font, text, _fontSize, _maxWidth))
        , _material(
              std::make_unique<renderer::vulkan::Material>(_id, renderer, pipeline, _texture.get()))
    {}

    const std::string &TextLabel::getId() const
    {
        return _id;
    }

    const std::string &TextLabel::getFont() const
    {
        return _font;
    }

    unsigned TextLabel::getFontSize() const
    {
        return _fontSize;
    }

    const std::string &TextLabel::getText() const
    {
        return _text;
    }

    const glm::vec4 &TextLabel::getColor() const
    {
        return _color;
    }

    const renderer::vulkan::Material *TextLabel::getMaterial() const
    {
        return _material.get();
    }

    HorizontalAlignment TextLabel::getHorizontalAlignment() const
    {
        return _horizontalAlignment;
    }

    VerticalAlignment TextLabel::getVerticalAlignment() const
    {
        return _verticalAlignment;
    }

    glm::mat4 TextLabel::textMatrix(const glm::mat4 &boxMatrix, const glm::vec2 &boxPixelSize) const
    {
        const images::P2PGM &image = _texture->getGrayTextureImage();
        float atlasWidth = static_cast<float>(image.getWidth());
        float atlasHeight = static_cast<float>(image.getHeight());

        float widthFraction;
        float heightFraction;
        if (_horizontalAlignment == HorizontalAlignment::JUSTIFY)
        {
            widthFraction = 1.0f;
            heightFraction = 1.0f;
        }
        else
        {
            widthFraction = boxPixelSize.x > 0.0f ? atlasWidth / boxPixelSize.x : 0.0f;
            heightFraction = boxPixelSize.y > 0.0f ? atlasHeight / boxPixelSize.y : 0.0f;
        }

        float offsetX = 0.0f;
        switch (_horizontalAlignment)
        {
        case HorizontalAlignment::LEFT:
            offsetX = -0.5f + widthFraction / 2.0f;
            break;
        case HorizontalAlignment::RIGHT:
            offsetX = 0.5f - widthFraction / 2.0f;
            break;
        case HorizontalAlignment::CENTER:
        case HorizontalAlignment::JUSTIFY:
            offsetX = 0.0f;
            break;
        }

        float offsetY = 0.0f;
        switch (_verticalAlignment)
        {
        case VerticalAlignment::TOP:
            offsetY = -0.5f + heightFraction / 2.0f;
            break;
        case VerticalAlignment::BOTTOM:
            offsetY = 0.5f - heightFraction / 2.0f;
            break;
        case VerticalAlignment::CENTER:
            offsetY = 0.0f;
            break;
        }

        glm::mat4 local = glm::translate(glm::mat4(1.0f), glm::vec3(offsetX, offsetY, 0.0f))
            * glm::scale(glm::mat4(1.0f), glm::vec3(widthFraction, heightFraction, 1.0f));
        return boxMatrix * local;
    }

    void TextLabel::setColor(const glm::vec4 &color)
    {
        _color = color;
    }

    void TextLabel::setText(const std::string &text)
    {
        if (text == _text)
        {
            return;
        }
        _text = text;
        renderer::vulkan::TextureType newTexture =
            _fontManager.loadText(_renderer, _font, text, _fontSize, _maxWidth);
        _renderer.deferFreeTexture(std::move(_texture));
        _texture = std::move(newTexture);
        _material->setTexture(_texture.get());
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, const TextLabel &label)
    {
        std::vector<float> colorVector = { label.getColor()[0], label.getColor()[1],
                                           label.getColor()[2] };
        out << YAML::BeginMap << BRASIO_YAML_KV(id, label.getId())
            << BRASIO_YAML_KV(font, label.getFont()) << BRASIO_YAML_KV(size, label.getFontSize())
            << BRASIO_YAML_KV(value, label.getText())
            << BRASIO_YAML_KV(color, YAML::Flow << colorVector) << YAML::Key << "alignment"
            << YAML::Value << YAML::BeginMap
            << BRASIO_YAML_KV(horizontal,
                              horizontalAlignmentToString(label.getHorizontalAlignment()))
            << BRASIO_YAML_KV(vertical, verticalAlignmentToString(label.getVerticalAlignment()))
            << YAML::EndMap << YAML::EndMap;
        return out;
    }
} // namespace brasio::scenes
