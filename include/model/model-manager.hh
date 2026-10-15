#pragma once

#include <model/model.hh>
#include <core/manager.hh>

#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::model
{
    class ModelManager : public core::Manager<std::string, Model>
    {
    public:
        ModelManager(const renderer::vulkan::VulkanRenderer &renderer);

        virtual ModelType createObject(const YAML::Node &config) override;

    private:
        const renderer::vulkan::VulkanRenderer &_renderer;
    };
} // namespace brasio::model
