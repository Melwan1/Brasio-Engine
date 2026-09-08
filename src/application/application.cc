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
        _renderer.reset();
        BRASIO_LOG_DEBUG("Destroying window", { "APPLICATION", "TEARDOWN" });
        glfwDestroyWindow(_window);
        _window = nullptr;
        BRASIO_LOG_DEBUG("Terminating glfw", { "APPLICATION", "TEARDOWN" });
        glfwTerminate();
    }

    GLFWwindow *Application::getWindow() const
    {
        return _window;
    }

    void Application::initListeners()
    {
        BRASIO_LOG_TRACE("Creating event listeners", { "APPLICATION", "SETUP" });
        ApplicationEventEmitter::addListener(*this);
        KeyboardEventEmitter::addListener(*this);
        MouseEventEmitter::addListener(*this);
        WindowEventEmitter::addListener(*this);
    }

    bool Application::init(const YAML::Node &config)
    {
        io::logging::Logger::fromConfig(config["logging"]);
        BRASIO_LOG_DEBUG("Configured logger", { "APPLICATION", "SETUP" });

        if (!glfwInit())
        {
            BRASIO_LOG_CRITICAL("Unable to initialize GLFW", { "APPLICATION", "SETUP" });
            return false;
        }

        bool useOpengl = !config["renderer"]["type"]
            || !config["renderer"]["type"].as<std::string>().compare("OpenGL");

        BRASIO_LOG_DEBUG("Setting up window", { "APPLICATION", "SETUP" });

        if (!setupWindow(config["application"]["window"], useOpengl))
        {
            BRASIO_LOG_ERROR("Could not setup window", { "APPLICATION", "SETUP" });
            return false;
        }

        setupGlfwInput();

        if (useOpengl && glewInit() != GLEW_OK)
        {
            BRASIO_LOG_ERROR("Unable to initialize GLEW", { "APPLICATION", "SETUP" });
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
            _title.c_str(), monitor, nullptr);
        (void)mode;
        if (!window)
        {
            BRASIO_LOG_CRITICAL("Unable to create GLFW window.", { "APPLICATION", "SETUP" });
            return false;
        }
        _window = window;
        BRASIO_LOG_DEBUG("Created window at monitor index " + std::to_string(monitorIndex) + " out of " + std::to_string(monitorCount)  + " monitors", { "APPLICATION", "SETUP" });

        glfwMakeContextCurrent(window);

        return true;
    }

    void Application::setupGlfwInput()
    {
        BRASIO_LOG_TRACE("Setting up glfw input", { "APPLICATION", "SETUP" });
        glfwSetInputMode(getWindow(), GLFW_LOCK_KEY_MODS, GLFW_TRUE);
    }

    void Application::setupCallbacks()
    {
        BRASIO_LOG_TRACE("Setting up callbacks", { "APPLICATION", "SETUP" });
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
            BRASIO_LOG_DEBUG("Setting application version from latest git tag", { "APPLICATION", "SETUP" });
            return setVersionFromGit();
        case VersionControlType::CONFIG_FILE:
            BRASIO_LOG_DEBUG("Setting application version from config file", { "APPLICATION", "SETUP" });
            return setVersionFromConfig(applicationConfig["version"]);
        default:
            BRASIO_LOG_WARNING("Did not set application version", { "APPLICATION", "SETUP" });
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
            BRASIO_LOG_WARNING(
                "Could not execute git command to fetch tags",
                { "APPLICATION", "SETUP" });
            return false;
        }
        std::ifstream tagFileContent(tagFilePath.string(), std::ios::ate);
        size_t fileSize = tagFileContent.tellg();
        if (fileSize == 0)
        {
            BRASIO_LOG_WARNING("Could not find any tag", { "APPLICATION", "SETUP" });
            return false;
        }
        std::string tag(fileSize, 0);
        tagFileContent.seekg(0);
        tagFileContent.read(tag.data(),
                            fileSize - 1); // omit newline at end of file
        _version = utils::Version(tag);
        BRASIO_LOG_DEBUG("Setting application version to " + _version.toString(), { "APPLICATION", "SETUP" });
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
