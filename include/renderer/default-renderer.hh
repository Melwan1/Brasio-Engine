#pragma once

#include <renderer/renderer.hh>

#include <yaml-cpp/yaml.h>

namespace brasio::renderer
{

    class DefaultRenderer;

    using DefaultRendererType = std::unique_ptr<DefaultRenderer>;

    /**
     * The default renderer.
     *
     * Does nothing.
     */
    class DefaultRenderer : public Renderer
    {
    public:
        DefaultRenderer();

        virtual void init() override;
        virtual void drawFrame() override;

        static DefaultRendererType fromConfig(const YAML::Node &config);
    };
} // namespace brasio::renderer
