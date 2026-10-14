#pragma once

#include <renderer/renderer.hh>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

#include <yaml-cpp/yaml.h>

#include <renderer/vulkan/command-pool.hh>
#include <renderer/vulkan/depth-attachment.hh>
#include <renderer/vulkan/image-attachment.hh>
#include <renderer/vulkan/instance.hh>
#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/physical-device.hh>
#include <renderer/vulkan/render-pass.hh>
#include <renderer/vulkan/surface.hh>
#include <renderer/vulkan/swapchain.hh>
#include <renderer/vulkan/sync-objects.hh>

#include <shaders/shader-manager.hh>

namespace brasio::renderer::vulkan
{
    class CommandBufferArray;
    using CommandBufferArrayType = std::unique_ptr<CommandBufferArray>;
} // namespace brasio::renderer::vulkan

namespace brasio::renderer::vulkan
{

    class VulkanRenderer;
    class Material;

    using VulkanRendererType = std::unique_ptr<VulkanRenderer>;

    /**
     * The Vulkan Renderer.
     *
     * Uses Vulkan as the base API to renderer objects to the window.
     */

    class VulkanRenderer : public Renderer
    {
    public:
        VulkanRenderer(GLFWwindow *window, const YAML::Node &config);

        ~VulkanRenderer();

        virtual void init() override;
        virtual void drawFrame(Renderable &root) override;

        void waitIdle() const;

        void pickPhysicalDevice();
        void createLogicalDevice();

        void createSwapChain();
        void createSwapChain(VkPresentModeKHR presentMode);
        void createSwapChain(const YAML::Node &config);

        void createImageViews();

        void createRenderPass();

        void createCommandPool();
        void createCommandBuffers();

        void createSyncObjects();

        void cleanupSwapChain();
        void recreateSwapChain();

        void createDepthResources();
        void createColorResources();

        bool isMultisampled() const;

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
        const CommandBufferArrayType &getCommandBuffers() const;
        unsigned getMaxFramesInFlight() const;
        uint32_t getCurrentFrame() const;

        const shaders::ShaderManager &getShaderManager() const;

        static VulkanRendererType fromConfig(const YAML::Node &config, GLFWwindow *window);

    private:
        std::vector<VkImageView> framebufferAttachmentViews() const;

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

        CommandPoolType _commandPool;
        CommandBufferArrayType _commandBuffers;

        SyncObjectsType _syncObjects;

        DepthAttachmentType _depthAttachment;
        ImageAttachmentType _colorAttachment;

        VkSampleCountFlagBits _msaaSamples = VK_SAMPLE_COUNT_1_BIT;
        uint32_t _currentFrame = 0;
    };
} // namespace brasio::renderer::vulkan
