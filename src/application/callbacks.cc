#include <application/callbacks.hh>

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods)
{
    Application *application =
        static_cast<Application *>(glfwGetWindowUserPointer(window));
    if (!application)
    {
        std::cerr << "Discarding Keyboard event due to no application linked "
                     "to the window."
                  << std::endl;
        return;
    }
    switch (action)
    {
    case GLFW_PRESS: {
        KeyboardPressEvent event =
            KeyboardPressEvent::create(key, scancode, mods);
        application->KeyboardEventEmitter::fire(event);
        break;
    }
    case GLFW_REPEAT: {
        KeyboardLongPressEvent event =
            KeyboardLongPressEvent::create(key, scancode, mods);
        application->KeyboardEventEmitter::fire(event);
        break;
    }
    case GLFW_RELEASE: {
        KeyboardReleaseEvent event =
            KeyboardReleaseEvent::create(key, scancode, mods);
        application->KeyboardEventEmitter::fire(event);
        break;
    }
    }
}

void windowCloseCallback(GLFWwindow *window)
{
    Application *application =
        static_cast<Application *>(glfwGetWindowUserPointer(window));
    if (!application)
    {
        std::cerr << "Discarding Window close event due to no application "
                     "linked to the window."
                  << std::endl;
        return;
    }
    WindowCloseEvent event;
    application->WindowEventEmitter::fire(event);
}
