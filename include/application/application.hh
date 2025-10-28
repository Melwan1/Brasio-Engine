#pragma once

#include <application/libapplication.hh>
#include <events/emitters/emitters.hh>
#include <events/listeners/listeners.hh>

class Application
    : public ApplicationEventEmitter
    , public ApplicationEventListener
    , public KeyboardEventEmitter
    , public KeyboardEventListener
    , public MouseEventEmitter
    , public MouseEventListener
    , public WindowEventEmitter
    , public WindowEventListener
{
public:
    Application();
    ~Application();

    GLFWwindow *getWindow() const;

    void initListeners();
    bool init();

    // various setups

    /** Setup the window on which to render the application.
     * @param monitorIndex the index of the monitor on which the window must be
     * displayed. If \c monitorIndex is -1, the last monitor is used. If it is
     * greater or equal to the number of monitors, the last monitor is used.
     * Any other input is considered invalid and throws an exception.
     *
     * @return true if the window has been created correctly, false otherwise.
     */
    bool setupWindow(int monitorIndex);

    void setupGlfwInput();
    void setupCallbacks();

    void loop();

    virtual void onEvent(ApplicationRenderEvent &event) override;
    virtual void onEvent(ApplicationTickEvent &event) override;
    virtual void onEvent(ApplicationUpdateEvent &event) override;
    virtual void onEvent(KeyboardPressEvent &event) override;
    virtual void onEvent(WindowCloseEvent &event) override;

private:
    GLFWwindow *_window;

    bool _shouldTerminate;
};
