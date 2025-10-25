#include <application/libapplication.hh>

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
