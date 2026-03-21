#pragma once

#include <vulkan/vulkan_core.h>

#include <memory>

#include <core/handler.hh>
#include <renderer/vulkan/buffer.hh>

namespace brasio::renderer::vulkan
{

    class DescriptorSets : public core::Handler<std::vector<VkDescriptorSet>>
    {
    public:
        DescriptorSets(const VkDevice &logicalDevice,
                       const VkDescriptorSetAllocateInfo &allocateInfo);

        void update(const std::vector<BufferType> &buffers);

    private:
        const VkDevice &_logicalDevice;
    };

    using DescriptorSetsType = std::unique_ptr<DescriptorSets>;

} // namespace brasio::renderer::vulkan
