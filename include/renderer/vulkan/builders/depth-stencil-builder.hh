#pragma once

#include <core/builder.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{
    class DepthStencilBuilder : public core::Builder<VkPipelineDepthStencilStateCreateInfo>
    {

        public:

            DepthStencilBuilder();

            virtual DepthStencilBuilder &base() override;
            virtual VkPipelineDepthStencilStateCreateInfo build() override;

        private:

            VkStructureType _structureType;
    };
}
