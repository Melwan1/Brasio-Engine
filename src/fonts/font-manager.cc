#include <fonts/font-manager.hh>
#include <io/logging/logger.hh>
#include <renderer/vulkan/builders/texture-builder.hh>

namespace brasio::fonts
{
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
                          const std::string &fontName, const std::string &text, unsigned fontSize)
    {
        if (!_faces.contains(fontName))
        {
            BRASIO_LOG_CRITICAL("Could not load text \"" + text + "\" with font " + fontName,
                                { "FONTS" });
        }
        FT_Face face = _faces[fontName];
        unsigned dpi = 300;
        FT_Set_Char_Size(face, 0, fontSize * 64, 0, dpi);
        for (char character : text)
        {
            if (FT_Load_Char(face, character, FT_LOAD_RENDER))
            {
                BRASIO_LOG_CRITICAL("Could not get glyph index of character "
                                        + std::string(character, 1),
                                    { "FONTS" });
            }
            if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP
                && FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
            {
                BRASIO_LOG_CRITICAL("Could not render glyph to bitmap for character "
                                        + std::string(character, 1),
                                    { "FONTS" });
            }
            FT_GlyphSlot slot = face->glyph;
            (void)slot;
        }
        images::P2PGM textureImage{}; // TODO: build this shit
        return renderer::vulkan::builders::TextureBuilder(renderer)
            .withTextureImage(textureImage)
            .build();
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
