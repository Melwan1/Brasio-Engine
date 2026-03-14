#pragma once

#include <optional>
#include <cstdint>

namespace brasio::renderer::vulkan
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete();
    };
} // namespace brasio::renderer::vulkan
