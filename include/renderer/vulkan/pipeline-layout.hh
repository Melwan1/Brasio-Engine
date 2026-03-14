#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>
#include <renderer/vulkan/logical-device.hh>

namespace brasio::renderer::vulkan
{
    class PipelineLayout : public core::Handler<VkPipelineLayout>
    {
    public:
        PipelineLayout(const VkDevice &logicalDevice,
                       const VkPipelineLayoutCreateInfo &createInfo);
    };

    using PipelineLayoutType = std::unique_ptr<PipelineLayout>;
} // namespace brasio::renderer::vulkan
