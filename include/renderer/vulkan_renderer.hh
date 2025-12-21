#pragma once

#include <renderer/renderer.hh>

#include <vulkan/vulkan.hpp>

#include <ostream>

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

    virtual void init() override;

    void print_extensions(std::ostream &ostr);

private:
    VkInstance _instance;
    uint32_t _extensionCount;
    std::vector<VkExtensionProperties> _extensions;
};
