#pragma once

#include <memory>

#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

class Surface
{
public:
    Surface(const VkInstance &instance, GLFWwindow *window);
    ~Surface();

    const VkSurfaceKHR &getHandle() const;
    VkSurfaceKHR &getHandle();

private:
    VkInstance _instance;
    GLFWwindow *_window;
    VkSurfaceKHR _surface;
};

using SurfaceType = std::unique_ptr<Surface>;
