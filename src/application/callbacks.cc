#include <application/callbacks.hh>

namespace brasio::application
{

    void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                     int mods)
    {
        Application *application =
            static_cast<Application *>(glfwGetWindowUserPointer(window));
        if (!application)
        {
            std::cerr
                << "Discarding Keyboard event due to no application linked "
                   "to the window."
                << std::endl;
            return;
        }
        switch (action)
        {
        case GLFW_PRESS: {
            events::subevents::KeyboardPressEvent event =
                events::subevents::KeyboardPressEvent::create(key, scancode,
                                                              mods);
            application->KeyboardEventEmitter::fire(event);
            break;
        }
        case GLFW_REPEAT: {
            events::subevents::KeyboardLongPressEvent event =
                events::subevents::KeyboardLongPressEvent::create(key, scancode,
                                                                  mods);
            application->KeyboardEventEmitter::fire(event);
            break;
        }
        case GLFW_RELEASE: {
            events::subevents::KeyboardReleaseEvent event =
                events::subevents::KeyboardReleaseEvent::create(key, scancode,
                                                                mods);
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
        events::subevents::WindowCloseEvent event;
        application->WindowEventEmitter::fire(event);
    }

    void framebufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        Application *application =
            reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
        if (!application)
        {
            std::cerr << "Discarding Window resize event due to no application "
                         "linked to the window."
                      << std::endl;
            return;
        }
        events::subevents::WindowResizeEvent event(
            false, static_cast<unsigned>(width), static_cast<unsigned>(height));
        application->WindowEventEmitter::fire(event);
    }
} // namespace brasio::application
