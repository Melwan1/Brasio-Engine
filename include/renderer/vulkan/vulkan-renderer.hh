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
#include <renderer/vulkan/descriptor-pool.hh>
#include <renderer/vulkan/descriptor-set-layout.hh>
#include <renderer/vulkan/descriptor-sets.hh>
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

namespace brasio::renderer::vulkan
{
    class CommandBufferArray;
    using CommandBufferArrayType = std::unique_ptr<CommandBufferArray>;
} // namespace brasio::renderer::vulkan

namespace brasio::renderer::vulkan
{
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
        void createUniformBuffers();

        void updateUniformBuffer(uint32_t currentImage);

        void createDescriptorSetLayout();
        void createDescriptorPool();
        void createDescriptorSets();

        // getters

        const Swapchain &getSwapchain() const;
        const RenderPass &getRenderPass() const;
        const PipelineLayout &getPipelineLayout() const;
        const GraphicsPipeline &getGraphicsPipeline() const;
        const CommandBufferArrayType &getCommandBuffers() const;
        const Buffer &getVertexBuffer() const;
        const Buffer &getIndexBuffer() const;
        const std::vector<uint16_t> &getIndices() const;
        const DescriptorSetLayout &getDescriptorSetLayout() const;
        const DescriptorSets &getDescriptorSets() const;
        uint32_t getCurrentFrame() const;

    private:
        GLFWwindow *_window;
        shaders::ShaderManager _shaderManager;
        std::vector<geometry::Vertex> _vertices;
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

        DescriptorSetLayoutType _descriptorSetLayout;
        std::vector<BufferType> _uniformBuffers;
        DescriptorPoolType _descriptorPool;
        DescriptorSetsType _descriptorSets;

        uint32_t _currentFrame = 0;
    };
} // namespace brasio::renderer::vulkan
