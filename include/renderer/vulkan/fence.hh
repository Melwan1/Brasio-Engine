#pragma once

#include <vulkan/vulkan_core.h>

#include <core/handler.hh>

class Fence : public Handler<VkFence>
{
public:
    Fence(const VkDevice &logicalDevice, const VkFenceCreateInfo &createInfo);
};
