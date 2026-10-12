#pragma once

#include <core/manager.hh>

#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::renderer::vulkan
{
    class TextureManager : public core::Manager<std::string, Texture>
    {
    public:
        TextureManager(const VulkanRenderer &renderer);

        virtual TextureType createObject(const YAML::Node &config) override;

    private:
        const VulkanRenderer &_renderer;
    };
} // namespace brasio::renderer::vulkan
