#pragma once

#include <memory>
#include <vector>

#include <model/model.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <renderer/vulkan/texture.hh>

namespace brasio::scenes
{

    class Scene;

    using SceneType = std::unique_ptr<Scene>;

    class Scene
    {
        public:
            Scene();

            void addModel(model::Model &model);
            void addTexture(renderer::vulkan::Texture &texture);

        private:

            std::vector<model::Model> _models;
            std::vector<renderer::vulkan::Texture> _textures;
            std::vector<SceneType> _subScenes;
    };
}
