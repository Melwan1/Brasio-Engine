#include <renderer/vulkan/texture-manager.hh>

#include <images/p2-pgm.hh>
#include <images/p3-ppm.hh>

#include <filesystem>

#include <renderer/vulkan/builders/texture-builder.hh>

namespace fs = std::filesystem;

namespace brasio::renderer::vulkan
{
    TextureManager::TextureManager(const VulkanRenderer &renderer)
        : _renderer(renderer)
    {}

    TextureType TextureManager::createObject(const YAML::Node &config)
    {
        builders::TextureBuilder builder(_renderer);
        const fs::path path = "assets" / fs::path(config["path"].as<std::string>());
        if (path.extension() == ".pgm")
        {
            builder.withTextureImage(images::P2PGM::load(path));
        }
        else if (path.extension() == ".ppm")
        {
            builder.withTextureImage(images::P3PPM::load(path));
        }
        return builder.build();
    }
} // namespace brasio::renderer::vulkan
