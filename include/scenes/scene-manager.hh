#pragma once

#include <core/manager.hh>

#include <string>
#include <set>

#include <scenes/scene-node.hh>
#include <scenes/branch-scene.hh>
#include <scenes/leaf-scene.hh>

#include <model/model-manager.hh>
#include <renderer/vulkan/material-manager.hh>

#include <yaml-cpp/yaml.h>
#include <glm/glm.hpp>

namespace brasio::scenes
{
    class SceneManager : public core::Manager<std::string, SceneNode>
    {
    public:
        SceneManager(const model::ModelManager &modelManager,
                     const renderer::vulkan::MaterialManager &materialManager);
        virtual SceneNodeType createObject(const YAML::Node &config) override;

        void load(const fs::path &directory, const std::string &rootSceneId);

        Transform parseTransform(const YAML::Node &transformConfig);
        SceneRectangle parseSceneRectangle(const YAML::Node &sceneRectangle);

        LeafSceneType parseLeafScene(const YAML::Node &config);
        BranchSceneType parseBranchScene(const YAML::Node &config);
        Drawable parseDrawable(const YAML::Node &config);

        SceneNode *getRoot() const;

    private:
        const model::ModelManager &_modelManager;
        const renderer::vulkan::MaterialManager &_materialManager;

        fs::path _directory;
        std::string _rootId;
        std::set<std::string> _visited;
    };
} // namespace brasio::scenes
