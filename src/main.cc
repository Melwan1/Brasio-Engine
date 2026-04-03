#include <application/libapplication.hh>

#include <yaml-cpp/yaml.h>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    fs::path config_path = "config/config.yaml";
    if (argc > 1)
    {
        config_path = argv[1];
    }
    brasio::application::ApplicationType application =
        brasio::application::Application::fromConfig(
            YAML::LoadFile(config_path));
    application->loop();
    return 0;
}
