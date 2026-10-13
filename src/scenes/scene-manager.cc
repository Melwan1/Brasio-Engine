#include <scenes/scene-manager.hh>
#include <scenes/draw-target.hh>

#include <filesystem>

namespace fs = std::filesystem;

namespace brasio::scenes
{

    SceneManager::SceneManager(const model::ModelManager &modelManager,
                               const renderer::vulkan::MaterialManager &materialManager)
        : _modelManager(modelManager)
        , _materialManager(materialManager)
    {}

    void SceneManager::load(const fs::path &directory, const std::string &rootSceneId)
    {
        _directory = directory;
        _rootId = rootSceneId;
        _visited.insert(rootSceneId);
        const fs::path rootPath = _directory / (rootSceneId + ".yaml");
        registerObject(rootSceneId, createObject(YAML::LoadFile(rootPath.string())));
    }

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
        if (config["children"])
        {
            BRASIO_LOG_ERROR("Leaf scene '" + config["id"].as<std::string>()
                                 + "' must not declare children, ignoring them",
                             { "CREATE", "SCENES" });
        }
        SceneRectangle sceneRectangle = parseSceneRectangle(config["scene_rectangle"]);
        std::vector<Drawable> drawables{};
        for (const YAML::Node &drawableNode : config["drawables"])
        {
            drawables.emplace_back(parseDrawable(drawableNode));
        }
        LeafSceneType leafScene = std::make_unique<LeafScene>(
            config["id"].as<std::string>(), sceneRectangle, drawTarget, std::move(drawables));
        BRASIO_LOG_DEBUG("Parsed leaf scene " + config["id"].as<std::string>(),
                         { "CREATE", "SCENES" });
        YAML::Emitter out;
        out << *leafScene;
        std::ostringstream oss;
        oss << "Scene config for id " << leafScene->getId() << " is:\n" << out.c_str();
        BRASIO_LOG_TRACE(oss.str(), { "CREATE", "SCENES" });
        return leafScene;
    }

    BranchSceneType SceneManager::parseBranchScene(const YAML::Node &config)
    {
        if (config["drawables"])
        {
            BRASIO_LOG_ERROR("Branch scene '" + config["id"].as<std::string>()
                                 + "' must not declare drawables, ignoring them",
                             { "CREATE", "SCENES" });
        }
        if (config["target"])
        {
            BRASIO_LOG_ERROR("Branch scene '" + config["id"].as<std::string>()
                                 + "' must not declare a target, ignoring it",
                             { "CREATE", "SCENES" });
        }
        SceneRectangle sceneRectangle = parseSceneRectangle(config["scene_rectangle"]);
        std::vector<SceneNodeType> subscenes;
        for (const YAML::Node &sceneConfig : config["children"])
        {
            const std::string sceneName = sceneConfig.as<std::string>();
            if (_visited.contains(sceneName))
            {
                BRASIO_LOG_INFO("Scene '" + sceneName
                                    + "' already loaded (cycle or duplicate reference), skipping",
                                { "CREATE", "SCENES" });
                continue;
            }
            _visited.insert(sceneName);
            const fs::path scenePath = _directory / (sceneName + ".yaml");
            subscenes.emplace_back(createObject(YAML::LoadFile(scenePath.string())));
        }
        BranchSceneType branchScene = std::make_unique<BranchScene>(
            config["id"].as<std::string>(), sceneRectangle, std::move(subscenes));
        BRASIO_LOG_DEBUG("Parsed branch scene " + config["id"].as<std::string>(),
                         { "CREATE", "SCENES" });
        YAML::Emitter out;
        out << *branchScene;
        std::ostringstream oss;
        oss << "Scene config for id " << branchScene->getId() << " is:\n" << out.c_str();
        BRASIO_LOG_TRACE(oss.str(), { "CREATE", "SCENES" });
        return branchScene;
    }

    Drawable SceneManager::parseDrawable(const YAML::Node &config)
    {
        model::Model *model = _modelManager.get(config["model"].as<std::string>());
        renderer::vulkan::Material *material =
            _materialManager.get(config["material"].as<std::string>());
        Transform transform = parseTransform(config["transform"]);
        if (!model || !material)
        {
            BRASIO_LOG_WARNING("Creating drawable with missing model or material",
                               { "CREATE", "SCENES" });
        }
        return { model, material, transform, transform.matrix() };
    }

    SceneRectangle SceneManager::parseSceneRectangle(const YAML::Node &config)
    {
        return { config["top"].as<unsigned>(), config["left"].as<unsigned>(),
                 config["width"].as<unsigned>(), config["height"].as<unsigned>() };
    }

    Transform SceneManager::parseTransform(const YAML::Node &config)
    {
        if (!config.IsMap())
        {
            if (config.as<std::string>().compare("identity"))
            {
                BRASIO_LOG_ERROR("Unrecognized transform config format, assuming identity",
                                 { "CREATE", "SCENES" });
            }
            return {};
        }
        Transform transform;
        transform.translation = { config["translation"][0].as<float>(),
                                  config["translation"][1].as<float>(),
                                  config["translation"][2].as<float>() };
        transform.rotation = { config["rotation"][0].as<float>(), config["rotation"][1].as<float>(),
                               config["rotation"][2].as<float>() };
        transform.scale = { config["scale"][0].as<float>(), config["scale"][1].as<float>(),
                            config["scale"][2].as<float>() };
        return transform;
    }

    SceneNode *SceneManager::getRoot() const
    {
        return get(_rootId);
    }

} // namespace brasio::scenes
