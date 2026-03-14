#pragma once

#include <renderer/renderer.hh>

namespace brasio::renderer
{
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
    };
} // namespace brasio::renderer
