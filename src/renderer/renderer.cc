#include <renderer/renderer.hh>

namespace brasio::renderer
{
    Renderer::Renderer()
    {}

    void Renderer::setResizedFramebuffer()
    {
        _resizedFramebuffer = true;
    }
} // namespace brasio::renderer
