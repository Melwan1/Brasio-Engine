#pragma once

#include <renderer/renderer.hh>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

#include <renderer/vulkan/builders/all.hh>
#include <renderer/vulkan/buffer.hh>
#include <renderer/vulkan/command-buffer-array.hh>
#include <renderer/vulkan/compute-pipeline.hh>
#include <renderer/vulkan/depth-attachment.hh>
#include <renderer/vulkan/descriptor-pool.hh>
#include <renderer/vulkan/descriptor-set-layout.hh>
#include <renderer/vulkan/descriptor-sets.hh>
#include <renderer/vulkan/graphics-pipeline.hh>
#include <renderer/vulkan/instance.hh>
#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/physical-device.hh>
#include <renderer/vulkan/pipeline-layout.hh>
#include <renderer/vulkan/queue-family-indices.hh>
#include <renderer/vulkan/render-pass.hh>
#include <renderer/vulkan/surface.hh>
#include <renderer/vulkan/swap-chain-support-details.hh>
#include <renderer/vulkan/swapchain.hh>
#include <renderer/vulkan/sync-objects.hh>
#include <renderer/vulkan/texture.hh>
#include <renderer/vulkan/texture-sampler.hh>
#include <shaders/shader-manager.hh>
#include <mesh/mesh.hh>

#include <yaml-cpp/yaml.h>

namespace brasio::renderer::vulkan
{
    class CommandBufferArray;
    using CommandBufferArrayType = std::unique_ptr<CommandBufferArray>;
} // namespace brasio::renderer::vulkan

namespace brasio::mesh
{
    class Mesh;
    using MeshType = std::unique_ptr<Mesh>;
} // namespace brasio::mesh

namespace brasio::renderer::vulkan
{

    class VulkanRenderer;

    using VulkanRendererType = std::unique_ptr<VulkanRenderer>;

    /**
     * The Vulkan Renderer.
     *
     * Uses Vulkan as the base API to renderer objects to the window.
     */

    class VulkanRenderer : public Renderer
    {
    public:
        VulkanRenderer(GLFWwindow *window);
        VulkanRenderer(GLFWwindow *window, const YAML::Node &config);

        ~VulkanRenderer();

        virtual void init() override;
        virtual void drawFrame() override;

        void pickPhysicalDevice();
        void createLogicalDevice();

        void createSwapChain();
        void createSwapChain(VkPresentModeKHR presentMode);
        void createSwapChain(const YAML::Node &config);

        void createImageViews();

        void createRenderPass();
        void createPipelines();
        void createPipelines(const YAML::Node &pipelineConfig);

        void createCommandPool();
        void createCommandBuffers();

        void createSyncObjects();

        void cleanupSwapChain();
        void recreateSwapChain();

        void createUniformBuffers();
        void createStorageBuffers();

        void updateUniformBuffer(uint32_t currentImage);

        void createDescriptorPool();
        void createDescriptorSets();
        void createTexture();

        void createDepthResources();
        void createColorResources();

        void runCompute();

        // getters

        GLFWwindow *getWindow() const;
        const VkInstance &getInstance() const;
        const VkSurfaceKHR &getSurface() const;
        const VkDevice &getLogicalDevice() const;
        const LogicalDevice &getLogicalDeviceWrapper() const;
        const VkPhysicalDevice &getPhysicalDevice() const;
        const PhysicalDevice &getPhysicalDeviceWrapper() const;

        const Swapchain &getSwapchain() const;
        const VkCommandPool &getCommandPool() const;
        const VkRenderPass &getRenderPass() const;
        const RenderPass &getRenderPassWrapper() const;
        const std::vector<GraphicsPipelineType> &getGraphicsPipelines() const;
        const std::vector<ComputePipelineType> &getComputePipelines() const;
        const CommandBufferArrayType &getCommandBuffers() const;
        const mesh::Mesh &getMesh1() const;
        const mesh::Mesh &getMesh2() const;
        const DescriptorSets &getDescriptorSets() const;
        const DescriptorSets &getComputeDescriptorSets() const;
        const VkBuffer &getParticleVertexBuffer() const;
        uint32_t getParticleCount() const;
        uint32_t getCurrentFrame() const;

        const shaders::ShaderManager &getShaderManager() const;

        static VulkanRendererType fromConfig(const YAML::Node &config, GLFWwindow *window);

    private:
        GLFWwindow *_window;
        shaders::ShaderManager _shaderManager;
        unsigned _maxFramesInFlight;
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
        std::vector<GraphicsPipelineType> _graphicsPipelines;
        std::vector<ComputePipelineType> _computePipelines;

        CommandPoolType _commandPool;
        mesh::MeshType _mesh1;
        mesh::MeshType _mesh2;
        CommandBufferArrayType _commandBuffers;

        SyncObjectsType _syncObjects;

        std::vector<BufferType> _uniformBuffers;
        std::vector<BufferType> _computeUniformBuffers;
        std::vector<BufferType> _storageBuffers;
        std::vector<TextureType> _textures;
        DescriptorPoolType _graphicsDescriptorPool;
        DescriptorPoolType _computeDescriptorPool;

        DepthAttachmentType _depthAttachment;
        ImageAttachmentType _colorAttachment;

        VkSampleCountFlagBits _msaaSamples = VK_SAMPLE_COUNT_1_BIT;
        uint32_t _currentFrame = 0;
    };
} // namespace brasio::renderer::vulkan
