#include "application/application.hh"
#include <application/libapplication.hh>
#include <application/callbacks.hh>

#include <events/libevents.hh>

#include <renderer/default-renderer.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

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
        std::map<std::string, io::logging::LogLevel> logLevelMap = {
            { "TRACE", io::logging::LogLevel::TRACE },
            { "DEBUG", io::logging::LogLevel::DEBUG },
            { "INFO", io::logging::LogLevel::INFO },
            { "WARNING", io::logging::LogLevel::WARNING },
            { "ERROR", io::logging::LogLevel::ERROR },
            { "CRITICAL", io::logging::LogLevel::CRITICAL }
        };
        io::logging::Logger::sLogLevel =
            logLevelMap.at(config["logging"]["level"].as<std::string>());

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
            /*renderer =
                std::make_unique<renderer::vulkan::VulkanRenderer>(_window);*/
            renderer = renderer::vulkan::VulkanRenderer::fromConfig(
                config["renderer"], _window);
        }
        if (!initRenderer(std::move(renderer)))
        {
            return false;
        }
        if (!setVersion(VersionControlType::LATEST_GIT_TAG,
                        config["application"]))
        {
            setVersion(VersionControlType::CONFIG_FILE, config["application"]);
        }
        std::string newTitle = _title + " v" + _version.toString();
        glfwSetWindowTitle(_window, newTitle.c_str());
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
        _title = windowConfig["title"].as<std::string>();
        GLFWwindow *window = glfwCreateWindow(
            windowConfig["width"].as<int>(), windowConfig["height"].as<int>(),
            _title.c_str(), nullptr /* monitor */, nullptr);
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

    bool Application::setVersion(enum VersionControlType versionControlType,
                                 const YAML::Node &applicationConfig)
    {
        switch (versionControlType)
        {
        case VersionControlType::LATEST_GIT_TAG:
            return setVersionFromGit();
        case VersionControlType::CONFIG_FILE:
            return setVersionFromConfig(applicationConfig["version"]);
        default:
            return false;
        }
    }

    bool Application::setVersionFromGit()
    {
        fs::path tagFilePath =
            "brasio-application-set-version-from-git-output.txt";
        // run git command
        std::string commandStr =
            "git tag | sort -r | head -n1 > " + tagFilePath.string();
        int returnCode = std::system(commandStr.c_str());
        if (returnCode != 0)
        {
            io::logging::Logger::warning(
                std::cout, "Could not execute git command to fetch tags",
                { "VERSION" });
            return false;
        }
        std::ifstream tagFileContent(tagFilePath.string(), std::ios::ate);
        size_t fileSize = tagFileContent.tellg();
        if (fileSize == 0)
        {
            return false; // no tag found
        }
        std::string tag(fileSize, 0);
        tagFileContent.seekg(0);
        tagFileContent.read(tag.data(),
                            fileSize - 1); // omit newline at end of file
        _version = utils::Version(tag);
        fs::remove(tagFilePath);
        return true;
    }

    bool Application::setVersionFromConfig(const YAML::Node &versionConfig)
    {
        if (!versionConfig)
        {
            return false;
        }
        _version = utils::Version(versionConfig.as<std::string>());
        return true;
    }
} // namespace brasio::application
