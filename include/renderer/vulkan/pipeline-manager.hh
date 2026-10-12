#pragma once

#include <core/manager.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <renderer/vulkan/pipeline.hh>

namespace brasio::renderer::vulkan
{
    class PipelineManager : public core::Manager<std::string, Pipeline>
    {
    public:
        PipelineManager(const VulkanRenderer &renderer);

        virtual PipelineType createObject(const YAML::Node &config) override;

    private:
        const VulkanRenderer &_renderer;
    };
} // namespace brasio::renderer::vulkan
