#include <renderer/vulkan/builders/surface-builder.hh>

namespace brasio::renderer::vulkan::builders
{
    SurfaceBuilder::SurfaceBuilder(const VulkanRenderer &renderer)
        : _renderer(renderer)
    {
        base();
    }

    SurfaceBuilder &SurfaceBuilder::base()
    {
        return *this;
    }

    SurfaceType SurfaceBuilder::build()
    {
        return std::make_unique<Surface>(_renderer);
    }
} // namespace brasio::renderer::vulkan::builders
