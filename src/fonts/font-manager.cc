#include <fonts/font-manager.hh>
#include <io/logging/logger.hh>
#include <renderer/vulkan/builders/texture-builder.hh>
#include <cstring>

namespace brasio::fonts
{
    FT_ULong FontManager::decodeUtf8(const std::string &text, size_t &index)
    {
        unsigned char first = static_cast<unsigned char>(text[index]);
        size_t extra;
        FT_ULong codepoint;
        if (first < 0x80)
        {
            codepoint = first;
            extra = 0;
        }
        else if ((first & 0xE0) == 0xC0)
        {
            codepoint = first & 0x1F;
            extra = 1;
        }
        else if ((first & 0xF0) == 0xE0)
        {
            codepoint = first & 0x0F;
            extra = 2;
        }
        else if ((first & 0xF8) == 0xF0)
        {
            codepoint = first & 0x07;
            extra = 3;
        }
        else
        {
            index++;
            return 0xFFFD;
        }
        index++;
        for (size_t i = 0; i < extra; i++)
        {
            if (index >= text.size() || (static_cast<unsigned char>(text[index]) & 0xC0) != 0x80)
            {
                return 0xFFFD;
            }
            codepoint = (codepoint << 6) | (static_cast<unsigned char>(text[index]) & 0x3F);
            index++;
        }
        return codepoint;
    }

    FontManager::FontManager()
    {
        if (FT_Init_FreeType(&_library))
        {
            BRASIO_LOG_CRITICAL("Failed to initialize font library", { "FONTS" });
        }
        BRASIO_LOG_TRACE("Initialized font library", { "FONTS" });
    }

    void FontManager::loadFontDirectory(const fs::path &fontDirectoryPath)
    {
        for (const auto &entry : fs::recursive_directory_iterator(fontDirectoryPath))
        {
            loadFont(entry);
        }
    }

    void FontManager::loadFont(const fs::path &fontPath)
    {
        FT_Face face;
        FT_Error error = FT_New_Face(_library, fontPath.string().c_str(), 0, &face);
        if (error == FT_Err_Unknown_File_Format)
        {
            BRASIO_LOG_CRITICAL("Failed to load font at " + fontPath.string()
                                    + ": unsupported font format",
                                { "FONTS" });
        }
        if (error)
        {
            BRASIO_LOG_CRITICAL("Failed to load font at " + fontPath.string()
                                    + ": file could not be opened or read",
                                { "FONTS" });
        }
        std::string fontName = fontPath.filename().replace_extension("");
        _faces.insert({ fontName, face });
        BRASIO_LOG_TRACE("Loaded font at " + fontPath.string() + ": internal name = " + fontName,
                         { "FONTS" });
        BRASIO_LOG_TRACE("Font has " + std::to_string(face->num_glyphs) + " glyphs", { "FONTS" });
        unsigned char_height = 16;
        unsigned dpi = 300;
        if (FT_Set_Char_Size(face, 0, char_height * 64, dpi, dpi))
        {
            BRASIO_LOG_CRITICAL("Failed to set pixel size for font " + fontName, { "FONTS" });
        }
        BRASIO_LOG_TRACE("Set pixel size to " + std::to_string(char_height)
                             + " with dpi = " + std::to_string(dpi),
                         { "FONTS" });
    }

    renderer::vulkan::TextureType
    FontManager::loadText(const renderer::vulkan::VulkanRenderer &renderer,
                          const std::string &fontName, const std::string &text, unsigned fontSize,
                          unsigned maxTextureWidth)
    {
        BRASIO_LOG_TRACE("Loading text: " + text, { "FONTS" });
        if (!_faces.contains(fontName))
        {
            BRASIO_LOG_CRITICAL("Could not load text \"" + text + "\" with font " + fontName,
                                { "FONTS" });
        }
        FT_Face face = _faces[fontName];
        unsigned dpi = 300;
        FT_Set_Char_Size(face, 0, fontSize * 64, 0, dpi);
        BRASIO_LOG_TRACE(
            "Max height: "
                + std::to_string((FT_MulFix(face->units_per_EM, face->size->metrics.y_scale)) >> 6),
            { "FONTS" });

        std::vector<images::P2PGM> characterImages{};
        unsigned totalLines = 1;
        unsigned lineWidth = 0;
        unsigned textureWidth = 0;
        for (size_t i = 0; i < text.size();)
        {
            FT_ULong codepoint = decodeUtf8(text, i);
            images::P2PGM characterImage = createCharacterImage(fontName, codepoint);
            unsigned charWidth = characterImage.getWidth();
            if (lineWidth + charWidth > maxTextureWidth)
            {
                totalLines++;
                lineWidth = 0;
            }
            lineWidth += charWidth;
            textureWidth = std::max(textureWidth, lineWidth);
            characterImages.emplace_back(std::move(characterImage));
        }
        unsigned lineHeight = characterImages.empty() ? 0 : characterImages.front().getHeight();
        unsigned textureHeight = totalLines * lineHeight;

        std::vector<unsigned char> textureData(textureHeight * textureWidth, 0);
        unsigned currentLine = 0;
        unsigned currentColumn = 0;
        for (const images::P2PGM &characterImage : characterImages)
        {
            unsigned charWidth = characterImage.getWidth();
            if (currentColumn + charWidth > maxTextureWidth)
            {
                currentLine++;
                currentColumn = 0;
            }
            for (size_t row = 0; row < characterImage.getHeight(); row++)
            {
                size_t textureRow = currentLine * lineHeight + row;
                for (size_t column = 0; column < charWidth; column++)
                {
                    size_t textureColumn = currentColumn + column;
                    textureData[textureRow * textureWidth + textureColumn] =
                        characterImage[row * charWidth + column];
                }
            }
            currentColumn += charWidth;
        }

        images::P2PGM textureImage(textureWidth, textureHeight, textureData);
        renderer::vulkan::TextureType texture = renderer::vulkan::builders::TextureBuilder(renderer)
                                                    .withTextureImage(textureImage)
                                                    .build();
        BRASIO_LOG_TRACE("Loaded text: " + text, { "FONTS" });
        return texture;
    }

    images::P2PGM FontManager::createCharacterImage(const std::string &fontName, FT_ULong codepoint)
    {
        FT_Face face = _faces[fontName];
        if (FT_Load_Char(face, codepoint, FT_LOAD_RENDER))
        {
            BRASIO_LOG_CRITICAL(
                "Could not get glyph index of codepoint " + std::to_string(codepoint), { "FONTS" });
        }
        if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP
            && FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
        {
            BRASIO_LOG_CRITICAL("Could not render glyph to bitmap for codepoint "
                                    + std::to_string(codepoint),
                                { "FONTS" });
        }
        FT_GlyphSlot slot = face->glyph;
        int ascent = FT_MulFix(face->bbox.yMax, face->size->metrics.y_scale) >> 6;
        int descent = FT_MulFix(face->bbox.yMin, face->size->metrics.y_scale) >> 6;
        unsigned height = ascent - descent;
        unsigned width = slot->advance.x >> 6;
        std::vector<unsigned char> bitmap(height * width, 0);
        for (size_t row = 0; row < slot->bitmap.rows; row++)
        {
            int bitmap_line = ascent - slot->bitmap_top + static_cast<int>(row);
            if (bitmap_line < 0 || bitmap_line >= static_cast<int>(height))
            {
                continue;
            }
            for (size_t column = 0; column < slot->bitmap.width; column++)
            {
                int bitmap_column = slot->bitmap_left + static_cast<int>(column);
                if (bitmap_column < 0 || bitmap_column >= static_cast<int>(width))
                {
                    continue;
                }
                bitmap[bitmap_line * width + bitmap_column] =
                    slot->bitmap.buffer[row * slot->bitmap.pitch + column];
            }
        }
        return { width, height, bitmap };
    }

    FontManager::~FontManager()
    {
        for (const auto &[fontName, face] : _faces)
        {
            FT_Done_Face(face);
            BRASIO_LOG_TRACE("Destroyed font " + fontName, { "FONTS" });
        }
        FT_Done_FreeType(_library);
        BRASIO_LOG_TRACE("Destroyed font library", { "FONTS" });
    }
} // namespace brasio::fonts
