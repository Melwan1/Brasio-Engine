#pragma once

#include <core/handler.hh>

#include <vulkan/vulkan_core.h>

#include <memory>

class CommandBufferArray : public Handler<std::vector<VkCommandBuffer>>
{
public:
    CommandBufferArray(const VkDevice &logicalDevice,
                       const VkCommandBufferAllocateInfo &allocateInfo);

    const VkCommandBuffer &at(uint32_t index);
};

using CommandBufferArrayType = std::unique_ptr<CommandBufferArray>;
