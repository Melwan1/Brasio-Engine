#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <filesystem>
#include <map>

#include <renderer/vulkan/texture.hh>

namespace fs = std::filesystem;

namespace brasio::fonts
{
    class FontManager
    {
    public:
        FontManager();

        void loadFontDirectory(const fs::path &fontDirectoryPath);
        void loadFont(const fs::path &fontPath);

        renderer::vulkan::TextureType loadText(const renderer::vulkan::VulkanRenderer &renderer,
                                               const std::string &fontName, const std::string &text,
                                               unsigned fontSize, unsigned maxTextureWidth);
        images::P2PGM createCharacterImage(const std::string &fontName, FT_ULong codepoint);

        ~FontManager();

    private:
        static FT_ULong decodeUtf8(const std::string &text, size_t &index);

        FT_Library _library;
        std::map<std::string, FT_Face> _faces;
    };
} // namespace brasio::fonts
