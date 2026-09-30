#pragma once

#include <core/handler.hh>
#include <renderer/vulkan/descriptor-sets.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

namespace brasio::renderer::vulkan
{
    class VulkanRenderer;

    class DescriptorPool : public core::Handler<VkDescriptorPool>
    {
    public:
        DescriptorPool(const VulkanRenderer &renderer,
                       const VkDescriptorPoolCreateInfo &createInfo);

        void setDescriptorSets(DescriptorSetsType descriptorSets);
        const DescriptorSets &getDescriptorSets() const;

    private:
        DescriptorSetsType _descriptorSets;
    };

    using DescriptorPoolType = std::unique_ptr<DescriptorPool>;
} // namespace brasio::renderer::vulkan
