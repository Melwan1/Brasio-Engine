#pragma once

#include <application/libapplication.hh>
#include <events/emitters/emitters.hh>
#include <events/listeners/listeners.hh>
#include <renderer/renderer.hh>

namespace brasio::application
{
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
        bool init();

        bool initRenderer(std::unique_ptr<renderer::Renderer> renderer);

        // various setups

        /** Setup the window on which to render the application.
         * @param monitorIndex the index of the monitor on which the window must
         * be displayed. If \c monitorIndex is -1, the last monitor is used. If
         * it is greater or equal to the number of monitors, the last monitor is
         * used. Any other input is considered invalid and throws an exception.
         *
         * @param use_opengl whether the window should initialize OpenGL
         * context.
         *
         * @return true if the window has been created correctly, false
         * otherwise.
         */
        bool setupWindow(int monitorIndex, bool useOpengl);

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

    private:
        GLFWwindow *_window;
        std::unique_ptr<renderer::Renderer> _renderer;

        bool _shouldTerminate;
    };
} // namespace brasio::application
