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
                                               unsigned fontSize);

        ~FontManager();

    private:
        FT_Library _library;
        std::map<std::string, FT_Face> _faces;
    };
} // namespace brasio::fonts
