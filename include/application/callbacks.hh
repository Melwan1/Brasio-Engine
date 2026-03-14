#pragma once

#include <application/application.hh>

namespace brasio::application
{
    void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                     int mods);
    void windowCloseCallback(GLFWwindow *window);
    void framebufferSizeCallback(GLFWwindow *window, int width, int height);
} // namespace brasio::application
