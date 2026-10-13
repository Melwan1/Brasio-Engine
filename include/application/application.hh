#pragma once

#include <application/libapplication.hh>
#include <events/emitters/emitters.hh>
#include <events/listeners/listeners.hh>
#include <renderer/renderer.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>
#include <fonts/font-manager.hh>

#include <renderer/vulkan/pipeline-manager.hh>
#include <renderer/vulkan/material-manager.hh>
#include <renderer/vulkan/texture-manager.hh>
#include <model/model-manager.hh>
#include <scenes/scene-manager.hh>

#include <yaml-cpp/yaml.h>

namespace brasio::application
{

    class Application;

    using ApplicationType = std::unique_ptr<Application>;

    class Application
        : public events::emitters::ApplicationEventEmitter
        , public events::listeners::ApplicationEventListener
        , public events::emitters::KeyboardEventEmitter
        , public events::listeners::KeyboardEventListener
        , public events::emitters::MouseEventEmitter
        , public events::listeners::MouseEventListener
        , public events::emitters::WindowEventEmitter
        , public events::listeners::WindowEventListener
    {
    public:
        Application();
        ~Application();

        GLFWwindow *getWindow() const;

        void initListeners();
        bool init(const YAML::Node &config);

        bool initRenderer(renderer::vulkan::VulkanRendererType renderer);
        void initFontManager();
        void initModelManager();
        void initTextureManager();
        void initPipelineManager();
        void initMaterialManager();
        void initSceneManager(const YAML::Node &scenesConfig);

        // various setups

        /** Setup the window on which to render the application.
         *
         * @param windowConfig the configuration of the window.
         *
         * @param useOpengl whether the renderer is OpenGL-based or not.
         *
         * @return true if the window has been created correctly, false
         * otherwise.
         */
        bool setupWindow(const YAML::Node &windowConfig, bool useOpengl);

        void setupGlfwInput();
        void setupCallbacks();

        void loop();

        virtual void onEvent(events::subevents::ApplicationRenderEvent &event) override;
        virtual void onEvent(events::subevents::ApplicationTickEvent &event) override;
        virtual void onEvent(events::subevents::ApplicationUpdateEvent &event) override;
        virtual void onEvent(events::subevents::KeyboardPressEvent &event) override;
        virtual void onEvent(events::subevents::WindowCloseEvent &event) override;
        virtual void onEvent(events::subevents::WindowResizeEvent &event) override;

        static ApplicationType fromConfig(const YAML::Node &node);
        bool setVersion(enum VersionControlType versionControlType,
                        const YAML::Node &applicationConfig);
        bool setVersionFromGit();
        bool setVersionFromConfig(const YAML::Node &versionConfig);

    private:
        GLFWwindow *_window;
        renderer::vulkan::VulkanRendererType _renderer;
        std::unique_ptr<fonts::FontManager> _fontManager;
        std::unique_ptr<model::ModelManager> _modelManager;
        std::unique_ptr<renderer::vulkan::TextureManager> _textureManager;
        std::unique_ptr<renderer::vulkan::PipelineManager> _pipelineManager;
        std::unique_ptr<renderer::vulkan::MaterialManager> _materialManager;
        std::unique_ptr<scenes::SceneManager> _sceneManager;
        std::string _title;
        utils::Version _version;

        bool _shouldTerminate;
    };
} // namespace brasio::application
