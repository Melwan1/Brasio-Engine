#pragma once

#include <application/libapplication.hh>
#include <events/emitters/emitters.hh>
#include <events/listeners/listeners.hh>
#include <renderer/renderer.hh>

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

        bool initRenderer(std::unique_ptr<renderer::Renderer> renderer);

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

        virtual void
        onEvent(events::subevents::ApplicationRenderEvent &event) override;
        virtual void
        onEvent(events::subevents::ApplicationTickEvent &event) override;
        virtual void
        onEvent(events::subevents::ApplicationUpdateEvent &event) override;
        virtual void
        onEvent(events::subevents::KeyboardPressEvent &event) override;
        virtual void
        onEvent(events::subevents::WindowCloseEvent &event) override;
        virtual void
        onEvent(events::subevents::WindowResizeEvent &event) override;

        static ApplicationType fromConfig(const YAML::Node &node);

    private:
        GLFWwindow *_window;
        std::unique_ptr<renderer::Renderer> _renderer;

        bool _shouldTerminate;
    };
} // namespace brasio::application
