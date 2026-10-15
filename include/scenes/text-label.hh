#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>
#include <yaml-cpp/yaml.h>

#include <renderer/vulkan/material.hh>
#include <renderer/vulkan/texture.hh>
#include <scenes/text-alignment.hh>

namespace brasio::fonts
{
    class FontManager;
}

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;
    class Pipeline;
} // namespace brasio::renderer::vulkan

namespace brasio::scenes
{
    class TextLabel
    {
    public:
        TextLabel(const std::string &id, const renderer::vulkan::VulkanRenderer &renderer,
                  fonts::FontManager &fontManager, const renderer::vulkan::Pipeline *pipeline,
                  const std::string &font, unsigned fontSize, unsigned maxWidth,
                  const std::string &text, const glm::vec4 &color = glm::vec4(1.0f),
                  HorizontalAlignment horizontalAlignment = HorizontalAlignment::LEFT,
                  VerticalAlignment verticalAlignment = VerticalAlignment::CENTER);

        const std::string &getId() const;
        const std::string &getFont() const;
        unsigned getFontSize() const;
        const std::string &getText() const;
        const glm::vec4 &getColor() const;
        const renderer::vulkan::Material *getMaterial() const;
        HorizontalAlignment getHorizontalAlignment() const;
        VerticalAlignment getVerticalAlignment() const;

        glm::mat4 textMatrix(const glm::mat4 &boxMatrix, const glm::vec2 &boxPixelSize) const;

        void setText(const std::string &text);
        void setColor(const glm::vec4 &color);

    private:
        std::string _id;
        const renderer::vulkan::VulkanRenderer &_renderer;
        fonts::FontManager &_fontManager;
        std::string _font;
        unsigned _fontSize;
        unsigned _maxWidth;
        std::string _text;
        glm::vec4 _color;
        HorizontalAlignment _horizontalAlignment;
        VerticalAlignment _verticalAlignment;
        renderer::vulkan::TextureType _texture;
        renderer::vulkan::MaterialType _material;
    };

    YAML::Emitter &operator<<(YAML::Emitter &out, const TextLabel &label);

    using TextLabelType = std::unique_ptr<TextLabel>;
} // namespace brasio::scenes
