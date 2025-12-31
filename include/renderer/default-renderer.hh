#pragma once

#include <renderer/renderer.hh>

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
