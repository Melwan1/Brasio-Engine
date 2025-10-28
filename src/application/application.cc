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
    GLFWwindow *window =
        glfwCreateWindow(1920, 1080, "Brasio Engine", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Unable to create GLFW window." << std::endl;
        return false;
    }

    _window = window;

    glfwMakeContextCurrent(window);

    setupGlfwInput();

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to setup GLEW." << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }

    glfwSetWindowUserPointer(window, this);

    initListeners();

    setupCallbacks();
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
        ApplicationTickEvent event;
        ApplicationEventEmitter::fire(event);
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}

void Application::onEvent(WindowCloseEvent &event)
{
    event.print(std::cout);
    std::cout << ESC_RESET << "\n";
    _shouldTerminate = true;
    event.handle();
}
