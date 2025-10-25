#pragma once

#include <application/libapplication.hh>

class Application
{
public:
    Application();
    ~Application();

    bool init();
    void loop();

private:
    GLFWwindow *_window;
};
