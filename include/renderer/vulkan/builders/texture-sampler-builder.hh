#pragma once

#include <vulkan/vulkan_core.h>
#include <core/builder.hh>
#include <renderer/vulkan/logical-device.hh>
#include <renderer/vulkan/physical-device.hh>
#include <renderer/vulkan/texture-sampler.hh>

namespace brasio::renderer::vulkan::builders {

    class TextureSamplerBuilder : public core::Builder<TextureSamplerType>
    {
        public:

            TextureSamplerBuilder(const PhysicalDeviceType &physicalDevice, const LogicalDeviceType &logicalDevice);

            TextureSamplerBuilder &base() override;
            TextureSamplerType build() override;

        private:

            VkStructureType _structureType;
            
            const PhysicalDeviceType &_physicalDevice;
            const LogicalDeviceType &_logicalDevice;

            VkFilter _magFilter;
            VkFilter _minFilter;
            VkSamplerAddressMode _addressModeU;
            VkSamplerAddressMode _addressModeV;
            VkSamplerAddressMode _addressModeW;
            VkBool32 _anisotropyEnable;

            VkBorderColor _borderColor;
            VkBool32 _unnormalizedCoordinates;
            VkBool32 _compareEnable;
            VkCompareOp _compareOp;
            VkSamplerMipmapMode _mipmapMode;
            float _mipLodBias;
            float _minLod;
            float _maxLod;
    };

}
