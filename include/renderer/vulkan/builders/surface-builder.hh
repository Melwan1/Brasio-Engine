#pragma once

#include <core/builder.hh>

#include <renderer/vulkan/surface.hh>

namespace brasio::renderer::vulkan::builders
{
    class SurfaceBuilder : public core::Builder<SurfaceType>
    {
    public:
        SurfaceBuilder(const VkInstance &instance, GLFWwindow *window);

        virtual SurfaceBuilder &base() override;
        virtual SurfaceType build() override;

    private:
        VkInstance _instance;
        GLFWwindow *_window;
    };
} // namespace brasio::renderer::vulkan::builders
