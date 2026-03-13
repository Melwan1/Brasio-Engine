#pragma once

#include <renderer/renderer.hh>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

#include <renderer/vulkan/builders/instance-builder.hh>
#include <renderer/vulkan/builders/surface-builder.hh>
#include <renderer/vulkan/builders/command-pool-builder.hh>
#include <renderer/vulkan/buffer.hh>
#include <renderer/vulkan/command-buffer-array.hh>
#include <renderer/vulkan/graphics-pipeline.hh>
#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/physical-device.hh>
#include <renderer/vulkan/pipeline-layout.hh>
#include <renderer/vulkan/queue-family-indices.hh>
#include <renderer/vulkan/render-pass.hh>
#include <renderer/vulkan/swap-chain-support-details.hh>
#include <renderer/vulkan/swapchain.hh>
#include <renderer/vulkan/sync-objects.hh>
#include <shaders/shader-manager.hh>
#include <geometry/vertex.hh>

/**
 * The Vulkan Renderer.
 *
 * Uses Vulkan as the base API to renderer objects to the window.
 */

class VulkanRenderer : public Renderer
{
public:
    VulkanRenderer(GLFWwindow *window);

    ~VulkanRenderer();

    virtual void init() override;
    virtual void drawFrame() override;

    void pickPhysicalDevice();
    void createLogicalDevice();

    void createSwapChain();

    void createImageViews();

    void createRenderPass();
    void createGraphicsPipeline();

    void createCommandPool();
    void createCommandBuffers();

    void createSyncObjects();

    void cleanupSwapChain();
    void recreateSwapChain();

    void createVertexBuffer();
    void createIndexBuffer();

private:
    GLFWwindow *_window;
    ShaderManager _shaderManager;
    std::vector<Vertex> _vertices;
    std::vector<uint16_t> _indices;

    InstanceType _instance;

#ifdef NDEBUG
    const bool _enableValidationLayers = false;
#else
    const bool _enableValidationLayers = true;
    std::vector<const char *> _validationLayers;
#endif /* ! NDEBUG */

    SurfaceType _surface;
    PhysicalDeviceType _physicalDevice;
    LogicalDeviceType _logicalDevice;
    SwapchainType _swapchain;
    RenderPassType _renderPass;
    PipelineLayoutType _pipelineLayout;
    GraphicsPipelineType _graphicsPipeline;

    CommandPoolType _commandPool;
    CommandBufferArrayType _commandBuffers;

    SyncObjectsType _syncObjects;

    BufferType _vertexBuffer;
    BufferType _indexBuffer;

    uint32_t _currentFrame = 0;
};
