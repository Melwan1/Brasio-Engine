#include <renderer/renderer.hh>

#include <renderer/default-renderer.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::renderer
{
    Renderer::Renderer()
    {}

    void Renderer::setResizedFramebuffer()
    {
        _resizedFramebuffer = true;
    }

    RendererType fromConfig(const YAML::Node &config)
    {
        if (!config["renderer"]["type"])
        {
            return DefaultRenderer::fromConfig(config);
        }
        if (!config["renderer"]["type"].as<std::string>().compare("Vulkan"))
        {
            return vulkan::VulkanRenderer::fromConfig(config, nullptr);
        }
        return DefaultRenderer::fromConfig(config);
    }

} // namespace brasio::renderer
