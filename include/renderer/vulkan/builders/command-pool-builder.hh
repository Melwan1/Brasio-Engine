#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/command-pool.hh>

class CommandPoolBuilder : public Builder<CommandPoolType>
{
public:
    CommandPoolBuilder(const VkDevice &logicalDevice);

    virtual CommandPoolBuilder &base() override;
    virtual CommandPoolType build() override;

    CommandPoolBuilder &withQueueFamilyIndex(uint32_t queueFamilyIndex);

private:
    VkDevice _logicalDevice;
    VkStructureType _structureType;
    uint32_t _queueFamilyIndex;
    VkCommandPoolResetFlags _resetFlags;
};
