#include <application/libapplication.hh>
#include <application/callbacks.hh>

#include <events/libevents.hh>

#include <renderer/default-renderer.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::application
{
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

    bool Application::init(const YAML::Node &config)
    {
        if (!glfwInit())
        {
            std::cerr << "Unable to initialize GLFW." << std::endl;
            return false;
        }

        bool useOpengl = !config["renderer"]["type"]
            || !config["renderer"]["type"].as<std::string>().compare("OpenGL");

        if (!setupWindow(config["application"]["window"], useOpengl))
        {
            return false;
        }

        setupGlfwInput();

        if (useOpengl && glewInit() != GLEW_OK)
        {
            std::cerr << "Unable to setup GLEW." << std::endl;
            glfwDestroyWindow(_window);
            glfwTerminate();
            return false;
        }

        glfwSetWindowUserPointer(_window, this);

        initListeners();

        setupCallbacks();
        std::unique_ptr<renderer::Renderer> renderer = nullptr;
        if (useOpengl)
        {
            renderer = std::make_unique<renderer::DefaultRenderer>();
        }
        else
        {
            renderer =
                std::make_unique<renderer::vulkan::VulkanRenderer>(_window);
        }
        if (!initRenderer(std::move(renderer)))
        {
            return false;
        }
        return true;
    }

    bool Application::initRenderer(std::unique_ptr<renderer::Renderer> renderer)
    {
        if (!renderer)
        {
            return false;
        }
        _renderer = std::move(renderer);
        _renderer->init();
        return true;
    }

    bool Application::setupWindow(const YAML::Node &windowConfig,
                                  bool useOpengl)
    {
        int monitorCount;
        GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);
        int monitorIndex = windowConfig["monitorIndex"].as<int>();
        if (monitorIndex >= monitorCount || monitorIndex == -1)
        {
            monitorIndex = monitorCount - 1;
        }
        if (!useOpengl)
        {
            // in case of Vulkan renderer, disable initialization of OpenGL
            // context
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        }
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
        GLFWmonitor *monitor = monitors[monitorIndex];
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        GLFWwindow *window = glfwCreateWindow(
            windowConfig["width"].as<int>(), windowConfig["height"].as<int>(),
            windowConfig["title"].as<std::string>().c_str(),
            nullptr /* monitor */, nullptr);
        (void)mode;
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
        glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);
    }

    void Application::loop()
    {
        while (!_shouldTerminate)
        {
            events::subevents::ApplicationTickEvent tickEvent;
            ApplicationEventEmitter::fire(tickEvent);
            glfwPollEvents();
        }
    }

    void Application::onEvent(events::subevents::ApplicationRenderEvent &event)
    {
        _renderer->drawFrame();
        event.handle();
    }

    void Application::onEvent(events::subevents::ApplicationTickEvent &event)
    {
        events::subevents::ApplicationRenderEvent renderEvent;
        ApplicationEventEmitter::fire(renderEvent);
        event.handle();
    }

    void Application::onEvent(events::subevents::ApplicationUpdateEvent &event)
    {
        events::subevents::ApplicationRenderEvent renderEvent;
        ApplicationEventEmitter::fire(renderEvent);
        event.handle();
    }

    void Application::onEvent(events::subevents::KeyboardPressEvent &event)
    {
        if (event.getPressedKey() == "ESC")
        {
            events::subevents::WindowCloseEvent windowCloseEvent;
            WindowEventEmitter::fire(windowCloseEvent);
        }
        event.handle();
    }

    void Application::onEvent(events::subevents::WindowCloseEvent &event)
    {
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
        _shouldTerminate = true;
        event.handle();
    }

    void Application::onEvent(events::subevents::WindowResizeEvent &event)
    {
        _renderer->setResizedFramebuffer();
        event.handle();
    }

    ApplicationType Application::fromConfig(const YAML::Node &config)
    {
        ApplicationType application = std::make_unique<Application>();
        application->init(config);
        return application;
    }
} // namespace brasio::application
