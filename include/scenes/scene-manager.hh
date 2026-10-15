#pragma once

#include <core/manager.hh>

#include <string>
#include <set>

#include <scenes/scene-node.hh>
#include <scenes/branch-scene.hh>
#include <scenes/leaf-scene.hh>

#include <model/model-manager.hh>
#include <renderer/vulkan/material-manager.hh>
#include <renderer/vulkan/pipeline-manager.hh>
#include <fonts/font-manager.hh>

#include <yaml-cpp/yaml.h>
#include <glm/glm.hpp>

namespace brasio::scenes
{
    class SceneManager : public core::Manager<std::string, SceneNode>
    {
    public:
        SceneManager(const model::ModelManager &modelManager,
                     const renderer::vulkan::MaterialManager &materialManager,
                     const renderer::vulkan::PipelineManager &pipelineManager,
                     fonts::FontManager &fontManager,
                     const renderer::vulkan::VulkanRenderer &renderer);
        virtual SceneNodeType createObject(const YAML::Node &config) override;

        void load(const fs::path &directory, const std::string &rootSceneId);

        Transform parseTransform(const YAML::Node &transformConfig);
        SceneRectangle parseSceneRectangle(const YAML::Node &sceneRectangle);

        LeafSceneType parseLeafScene(const YAML::Node &config);
        BranchSceneType parseBranchScene(const YAML::Node &config);
        Drawable parseDrawable(const YAML::Node &config, std::vector<TextLabelType> &textLabels);
        CameraType parseCamera(const YAML::Node &config, const SceneRectangle &sceneRectangle);

        SceneNode *getRoot() const;

    private:
        const model::ModelManager &_modelManager;
        const renderer::vulkan::MaterialManager &_materialManager;
        const renderer::vulkan::PipelineManager &_pipelineManager;
        fonts::FontManager &_fontManager;
        const renderer::vulkan::VulkanRenderer &_renderer;

        fs::path _directory;
        std::string _rootId;
        std::set<std::string> _visited;
    };
} // namespace brasio::scenes
