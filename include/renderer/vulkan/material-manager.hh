#pragma once

#include <core/manager.hh>

#include <renderer/vulkan/material.hh>
#include <renderer/vulkan/pipeline-manager.hh>
#include <renderer/vulkan/texture-manager.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::renderer::vulkan
{
    class MaterialManager : public core::Manager<std::string, Material>
    {
    public:
        MaterialManager(const VulkanRenderer &renderer, const PipelineManager &pipelineManager,
                        const TextureManager &textureManager);

        virtual MaterialType createObject(const YAML::Node &config) override;

    private:
        const VulkanRenderer &_renderer;
        const PipelineManager &_pipelineManager;
        const TextureManager &_textureManager;
    };
} // namespace brasio::renderer::vulkan
