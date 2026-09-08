#pragma once

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>

#include <renderer/vulkan/logical-device.hh>

namespace brasio::renderer::vulkan {

    class TextureSampler : public core::Handler<VkSampler> {
    
        public:

            TextureSampler(const LogicalDeviceType &logicalDevice, const VkSamplerCreateInfo &samplerInfo);

    };

    using TextureSamplerType = std::unique_ptr<TextureSampler>;
}
