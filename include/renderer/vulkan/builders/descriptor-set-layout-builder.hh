#pragma once

#include <core/builder.hh>

#include <vector>
#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/descriptor-set-layout.hh>

namespace brasio::renderer::vulkan::builders
{

    class DescriptorSetLayoutBuilder
        : public core::Builder<DescriptorSetLayoutType>
    {
    public:
        DescriptorSetLayoutBuilder(const VkDevice &logicalDevice);

        virtual DescriptorSetLayoutType build() override;
        virtual DescriptorSetLayoutBuilder &base() override;

        DescriptorSetLayoutBuilder &
        withBindings(const std::vector<VkDescriptorSetLayoutBinding> &bindings);

    private:
        VkDevice _logicalDevice;

        VkStructureType _structureType;
        std::vector<VkDescriptorSetLayoutBinding> _bindings;
    };

} // namespace brasio::renderer::vulkan::builders
