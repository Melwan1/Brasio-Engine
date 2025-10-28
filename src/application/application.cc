#include <application/libapplication.hh>
#include <application/callbacks.hh>

#include <events/libevents.hh>

Application::Application()
    : _window(nullptr)
    , _shouldTerminate(false)
{}

Application::~Application()
{
    glfwDestroyWindow(_window);
    _window = nullptr;
    glfwTerminate();
}

GLFWwindow *Application::getWindow() const
{
    return _window;
}

void Application::initListeners()
{
    ApplicationEventEmitter::addListener(*this);
    KeyboardEventEmitter::addListener(*this);
    MouseEventEmitter::addListener(*this);
    WindowEventEmitter::addListener(*this);
}

bool Application::init()
{
    if (!glfwInit())
    {
        std::cerr << "Unable to initialize GLFW." << std::endl;
        return false;
    }

    int monitorIndex = -1;
    if (!setupWindow(monitorIndex))
    {
        return false;
    }

    setupGlfwInput();

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to setup GLEW." << std::endl;
        glfwDestroyWindow(_window);
        glfwTerminate();
        return false;
    }

    glfwSetWindowUserPointer(_window, this);

    initListeners();

    setupCallbacks();
    return true;
}

bool Application::setupWindow(int monitorIndex)
{
    int monitorCount;
    GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);
    if (monitorIndex >= monitorCount || monitorIndex == -1)
    {
        monitorIndex = monitorCount - 1;
    }
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    GLFWmonitor *monitor = monitors[monitorIndex];
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height,
                                          "Brasio Engine", monitor, nullptr);
    if (!window)
    {
        std::cerr << "Unable to create GLFW window." << std::endl;
        return false;
    }
    _window = window;

    glfwMakeContextCurrent(window);

    return true;
}

void Application::setupGlfwInput()
{
    glfwSetInputMode(getWindow(), GLFW_LOCK_KEY_MODS, GLFW_TRUE);
}

void Application::setupCallbacks()
{
    glfwSetKeyCallback(_window, keyCallback);
    glfwSetWindowCloseCallback(_window, windowCloseCallback);
}

void Application::loop()
{
    while (!_shouldTerminate)
    {
        ApplicationTickEvent tickEvent;
        ApplicationEventEmitter::fire(tickEvent);
        glfwPollEvents();
    }
}

void Application::onEvent(ApplicationRenderEvent &event)
{
    event.print(std::cout);
    std::cout << "\n";
    glfwSwapBuffers(_window);
    event.handle();
}

void Application::onEvent(ApplicationTickEvent &event)
{
    event.print(std::cout);
    std::cout << "\n";
    ApplicationRenderEvent renderEvent;
    ApplicationEventEmitter::fire(renderEvent);
    event.handle();
}

void Application::onEvent(ApplicationUpdateEvent &event)
{
    event.print(std::cout);
    std::cout << "\n";
    ApplicationRenderEvent renderEvent;
    ApplicationEventEmitter::fire(renderEvent);
    event.handle();
}

void Application::onEvent(KeyboardPressEvent &event)
{
    event.print(std::cout);
    std::cout << "\n";
    if (event.getPressedKey() == "ESC")
    {
        WindowCloseEvent windowCloseEvent;
        WindowEventEmitter::fire(windowCloseEvent);
    }
    event.handle();
}

void Application::onEvent(WindowCloseEvent &event)
{
    event.print(std::cout);
    std::cout << "\n";
    glfwSetWindowShouldClose(_window, GLFW_TRUE);
    _shouldTerminate = true;
    event.handle();
}
