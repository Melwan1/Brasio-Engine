#pragma once

#include <renderer/renderer.hh>

#include <vulkan/vulkan.hpp>

/**
 * The Vulkan Renderer.
 *
 * Uses Vulkan as the base API to renderer objects to the window.
 */

class VulkanRenderer : public Renderer
{
public:
    VulkanRenderer();

    ~VulkanRenderer();

private:
    VkInstance _instance;
};
