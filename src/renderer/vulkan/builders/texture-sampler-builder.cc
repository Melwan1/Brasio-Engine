#include <renderer/vulkan/builders/texture-sampler-builder.hh>

namespace brasio::renderer::vulkan::builders {

    TextureSamplerBuilder::TextureSamplerBuilder(const PhysicalDeviceType &physicalDevice, const LogicalDeviceType &logicalDevice)
        : _physicalDevice(physicalDevice)
        , _logicalDevice(logicalDevice)
    {
        base();
    }

    TextureSamplerBuilder &TextureSamplerBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        _magFilter = VK_FILTER_LINEAR;
        _minFilter = VK_FILTER_LINEAR;
        _addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        _addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        _addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        _anisotropyEnable = VK_TRUE;

        _borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        _unnormalizedCoordinates = VK_FALSE;
        _compareEnable = VK_FALSE;
        _compareOp = VK_COMPARE_OP_ALWAYS;
        _mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        _mipLodBias = 0.0f;
        _minLod = 0.0f;
        _maxLod = 0.0f;
        return *this;
    }

    TextureSamplerType TextureSamplerBuilder::build()
    {
        VkSamplerCreateInfo samplerInfo{};
        samplerInfo.sType = _structureType;
        samplerInfo.magFilter = _magFilter;
        samplerInfo.minFilter = _minFilter;
        samplerInfo.addressModeU = _addressModeU;
        samplerInfo.addressModeV = _addressModeV;
        samplerInfo.addressModeW = _addressModeW;
        samplerInfo.anisotropyEnable = _anisotropyEnable;
        
        VkPhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(_physicalDevice->getHandle(), &properties);

        samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
        samplerInfo.borderColor = _borderColor;
        samplerInfo.unnormalizedCoordinates = _unnormalizedCoordinates;
        samplerInfo.compareEnable = _compareEnable;
        samplerInfo.compareOp = _compareOp;
        samplerInfo.mipmapMode = _mipmapMode;
        samplerInfo.mipLodBias = _mipLodBias;
        samplerInfo.minLod = _minLod;
        samplerInfo.maxLod = _maxLod;

        return std::make_unique<TextureSampler>(_logicalDevice, samplerInfo);

    }

}
