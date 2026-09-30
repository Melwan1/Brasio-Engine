#pragma once

#include <core/builder.hh>

#include <renderer/vulkan/surface.hh>

namespace brasio::renderer::vulkan::builders
{
    class SurfaceBuilder : public core::Builder<SurfaceType>
    {
    public:
        SurfaceBuilder(const VulkanRenderer &renderer);

        virtual SurfaceBuilder &base() override;
        virtual SurfaceType build() override;

    private:
        const VulkanRenderer &_renderer;
    };
} // namespace brasio::renderer::vulkan::builders
