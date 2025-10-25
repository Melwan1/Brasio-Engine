#pragma once

#include <application/libapplication.hh>

class Application
{
public:
    Application();
    ~Application();

    GLFWwindow *getWindow() const;

    bool init();
    void loop();

private:
    GLFWwindow *_window;
};
