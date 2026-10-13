#include <renderer/default-renderer.hh>

namespace brasio::renderer
{
    DefaultRenderer::DefaultRenderer()
    {}

    void DefaultRenderer::init()
    {}

    void DefaultRenderer::drawFrame(Renderable &root)
    {
        (void)root;
    }

    DefaultRendererType DefaultRenderer::fromConfig(const YAML::Node &config)
    {
        (void)config;
        return std::make_unique<DefaultRenderer>();
    }
} // namespace brasio::renderer
