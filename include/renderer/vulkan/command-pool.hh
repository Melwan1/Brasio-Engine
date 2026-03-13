#pragma once

#include <core/handler.hh>

#include <memory>

class CommandPool : public Handler<VkCommandPool>
{
public:
    CommandPool(const VkDevice &logicalDevice,
                const VkCommandPoolCreateInfo &createInfo);
};

using CommandPoolType = std::unique_ptr<CommandPool>;
