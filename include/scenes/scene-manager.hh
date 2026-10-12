#pragma once

#include <core/manager.hh>

#include <string>

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

        glm::mat4 parseTransform(const YAML::Node &transformConfig);
        SceneRectangle parseSceneRectangle(const YAML::Node &sceneRectangle);

        LeafSceneType parseLeafScene(const YAML::Node &config);
        BranchSceneType parseBranchScene(const YAML::Node &config);
        Drawable parseDrawable(const YAML::Node &config);

    private:
        const model::ModelManager &_modelManager;
        const renderer::vulkan::MaterialManager &_materialManager;
    };
} // namespace brasio::scenes
