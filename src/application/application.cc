#include <application/libapplication.hh>
#include <application/callbacks.hh>

Application::Application()
    : _window(nullptr)
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

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to setup GLEW." << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }

    _window = window;
    glfwSetWindowUserPointer(window, this);

    initListeners();

    glfwSetKeyCallback(window, keyCallback);
    return true;
}

void Application::loop()
{
    while (!glfwWindowShouldClose(_window))
    {
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}
