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

    void setupGlfwInput();
    void setupCallbacks();

    void loop();

    virtual void onEvent(WindowCloseEvent &event) override;

private:
    GLFWwindow *_window;

    bool _shouldTerminate;
};
