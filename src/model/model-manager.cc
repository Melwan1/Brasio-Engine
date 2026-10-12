#include <model/model-manager.hh>

namespace brasio::model
{
    ModelManager::ModelManager(const renderer::vulkan::VulkanRenderer &renderer)
        : _renderer(renderer)
    {
        registerObject("_unitQuad", Model::unitQuad());
    }

    ModelType ModelManager::createObject(const YAML::Node &config)
    {
        const fs::path path(config["path"].as<std::string>());
        io::files::OBJParser parser("assets" / path);
        parser.load();
        ModelType model = std::make_unique<Model>(parser);
        model->upload(_renderer);
        return model;
    }
} // namespace brasio::model
