#pragma once

#include <renderer/renderer.hh>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

#include <renderer/vulkan/builders/instance-builder.hh>
#include <renderer/vulkan/builders/surface-builder.hh>
#include <renderer/vulkan/queue-family-indices.hh>
#include <renderer/vulkan/swap-chain-support-details.hh>
#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/physical-device.hh>
#include <renderer/vulkan/render-pass.hh>
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
    QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &device);

    void createLogicalDevice();
    void getDeviceQueues(const QueueFamilyIndices &indices);

    void createSwapChain();

    void createImageViews();

    void createRenderPass();
    void createGraphicsPipeline();

    void createCommandPool();
    void createCommandBuffers();

    void recordCommandBuffer(VkCommandBuffer commandBuffer,
                             uint32_t imageIndex);

    void createSyncObjects();

    void cleanupSwapChain();
    void recreateSwapChain();

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                      VkMemoryPropertyFlags properties, VkBuffer &buffer,
                      VkDeviceMemory &bufferMemory);
    void createVertexBuffer();
    void createIndexBuffer();
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

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

    VkPipelineLayout _pipelineLayout;
    VkPipeline _graphicsPipeline;

    VkCommandPool _commandPool;
    std::vector<VkCommandBuffer> _commandBuffers;

    SyncObjectsType _syncObjects;

    VkBuffer _vertexBuffer;
    VkDeviceMemory _vertexBufferMemory;

    VkBuffer _indexBuffer;
    VkDeviceMemory _indexBufferMemory;

    uint32_t findMemoryType(uint32_t typeFilter,
                            VkMemoryPropertyFlags properties);

    uint32_t _currentFrame = 0;
};
