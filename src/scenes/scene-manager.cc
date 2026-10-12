#include <scenes/scene-manager.hh>
#include <scenes/draw-target.hh>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <filesystem>

namespace fs = std::filesystem;

namespace brasio::scenes
{

    SceneManager::SceneManager(const model::ModelManager &modelManager,
                               const renderer::vulkan::MaterialManager &materialManager)
        : _modelManager(modelManager)
        , _materialManager(materialManager)
    {}

    SceneNodeType SceneManager::createObject(const YAML::Node &config)
    {
        if (!config["type"].as<std::string>().compare("LEAF"))
        {
            return parseLeafScene(config);
        }
        if (!config["type"].as<std::string>().compare("BRANCH"))
        {
            return parseBranchScene(config);
        }
        BRASIO_LOG_CRITICAL("Failed to parse scene: scene type must be LEAF or BRANCH",
                            { "CREATE", "SCENES" });
        return nullptr;
    }

    LeafSceneType SceneManager::parseLeafScene(const YAML::Node &config)
    {
        DrawTarget drawTarget = DrawTarget::SCREEN;
        if (!config["target"].as<std::string>().compare("SCREEN"))
        {
            drawTarget = DrawTarget::SCREEN;
        }
        else if (!config["target"].as<std::string>().compare("OFFSCREEN"))
        {
            drawTarget = DrawTarget::OFFSCREEN;
        }
        SceneRectangle sceneRectangle = parseSceneRectangle(config["scene_rectangle"]);
        std::vector<Drawable> drawables{};
        for (const YAML::Node &drawableNode : config["drawables"])
        {
            drawables.emplace_back(parseDrawable(drawableNode));
        }
        BRASIO_LOG_DEBUG("Parsed leaf scene " + config["id"].as<std::string>(),
                         { "CREATE", "SCENES" });
        return std::make_unique<LeafScene>(sceneRectangle, drawTarget, std::move(drawables));
    }

    BranchSceneType SceneManager::parseBranchScene(const YAML::Node &config)
    {
        SceneRectangle sceneRectangle = parseSceneRectangle(config["scene_rectangle"]);
        std::vector<SceneNodeType> subscenes;
        for (const YAML::Node &sceneConfig : config["children"])
        {
            const std::string sceneName = sceneConfig.as<std::string>();
            const fs::path scenePath = fs::path("config") / "scenes" / sceneName;
            subscenes.emplace_back(createObject(YAML::LoadFile(scenePath)));
        }
        BRASIO_LOG_DEBUG("Parsed branch scene " + config["id"].as<std::string>(),
                         { "CREATE", "SCENES" });
        return std::make_unique<BranchScene>(sceneRectangle, std::move(subscenes));
    }

    Drawable SceneManager::parseDrawable(const YAML::Node &config)
    {
        model::Model *model = _modelManager.get(config["model"].as<std::string>());
        renderer::vulkan::Material *material =
            _materialManager.get(config["material"].as<std::string>());
        glm::mat4 transform = parseTransform(config["transform"]);
        if (!model || !material)
        {
            BRASIO_LOG_WARNING("Creating drawable with missing model or material",
                               { "CREATE", "SCENES" });
        }
        return { &model->mesh(), material, transform };
    }

    SceneRectangle SceneManager::parseSceneRectangle(const YAML::Node &config)
    {
        return { config["top"].as<unsigned>(), config["left"].as<unsigned>(),
                 config["width"].as<unsigned>(), config["height"].as<unsigned>() };
    }

    glm::mat4 SceneManager::parseTransform(const YAML::Node &config)
    {
        if (!config.IsMap())
        {
            if (!config.as<std::string>().compare("identity"))
            {
                return glm::mat4(1.0f);
            }
            BRASIO_LOG_ERROR("Unrecognized transform config format, assuming identity",
                             { "CREATE", "SCENES" });
            return glm::mat4(1.0f);
        }
        glm::vec3 translation = { config["translation"][0].as<float>(),
                                  config["translation"][1].as<float>(),
                                  config["translation"][2].as<float>() };
        glm::vec3 rotation = { config["rotation"][0].as<float>(), config["rotation"][1].as<float>(),
                               config["rotation"][2].as<float>() };
        glm::vec3 scale = { config["scale"][0].as<float>(), config["scale"][1].as<float>(),
                            config["scale"][2].as<float>() };
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), translation)
            * glm::mat4_cast(glm::quat(glm::radians(rotation)))
            * glm::scale(glm::mat4(1.0f), scale);
        return transform;
    }

} // namespace brasio::scenes
