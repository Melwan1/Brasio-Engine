#include <renderer/vulkan/builders/surface-builder.hh>

SurfaceBuilder::SurfaceBuilder(const VkInstance &instance, GLFWwindow *window)
    : _instance(instance)
    , _window(window)
{
    base();
}

SurfaceBuilder &SurfaceBuilder::base()
{
    return *this;
}

SurfaceType SurfaceBuilder::build()
{
    return std::make_unique<Surface>(_instance, _window);
}
