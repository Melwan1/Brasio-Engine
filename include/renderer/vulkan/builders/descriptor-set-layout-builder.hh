#pragma once

#include <core/builder.hh>

#include <vector>
#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/descriptor-set-layout.hh>

namespace brasio::renderer::vulkan::builders
{

    class DescriptorSetLayoutBuilder : public core::Builder<DescriptorSetLayoutType>
    {
    public:
        DescriptorSetLayoutBuilder(const VkDevice &logicalDevice);

        virtual DescriptorSetLayoutType build() override;
        virtual DescriptorSetLayoutBuilder &base() override;

        DescriptorSetLayoutBuilder &
        withBindings(const std::vector<VkDescriptorSetLayoutBinding> &bindings);

        DescriptorSetLayoutBuilder &
        withUniformBuffers(uint32_t uniformBufferCount,
                           VkShaderStageFlagBits shaderStageFlags = VK_SHADER_STAGE_VERTEX_BIT);
        DescriptorSetLayoutBuilder &
        withStorageBuffers(uint32_t storageBufferCount,
                           VkShaderStageFlagBits shaderStageFlags = VK_SHADER_STAGE_COMPUTE_BIT);
        DescriptorSetLayoutBuilder &
        withTextures(uint32_t textureCount,
                     VkShaderStageFlagBits shaderStageFlags = VK_SHADER_STAGE_FRAGMENT_BIT);

    private:
        VkDevice _logicalDevice;

        VkStructureType _structureType;
        std::vector<VkDescriptorSetLayoutBinding> _bindings;
    };

} // namespace brasio::renderer::vulkan::builders
