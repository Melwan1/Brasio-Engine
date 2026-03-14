#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

#include <core/handler.hh>

namespace brasio::renderer::vulkan
{
    class Surface : public core::Handler<VkSurfaceKHR>
    {
    public:
        Surface(const VkInstance &instance, GLFWwindow *window);
    };

    using SurfaceType = std::unique_ptr<Surface>;
} // namespace brasio::renderer::vulkan
