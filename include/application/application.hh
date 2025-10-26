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
    void loop();

private:
    GLFWwindow *_window;
};
