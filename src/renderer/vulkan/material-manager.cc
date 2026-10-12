#include <renderer/vulkan/material-manager.hh>

namespace brasio::renderer::vulkan
{
    MaterialManager::MaterialManager(const VulkanRenderer &renderer,
                                     const PipelineManager &pipelineManager,
                                     const TextureManager &textureManager)
        : _renderer(renderer)
        , _pipelineManager(pipelineManager)
        , _textureManager(textureManager)
    {}

    MaterialType MaterialManager::createObject(const YAML::Node &config)
    {
        const Pipeline *pipeline = _pipelineManager.get(config["pipeline"].as<std::string>());

        const Texture *texture = nullptr;
        if (config["texture"])
        {
            texture = _textureManager.get(config["texture"].as<std::string>());
        }

        return std::make_unique<Material>(_renderer, pipeline, texture);
    }
} // namespace brasio::renderer::vulkan
