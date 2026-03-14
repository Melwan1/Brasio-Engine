#pragma once

#include <memory>
#include <vector>

#include <vulkan/vulkan_core.h>

#include <renderer/vulkan/fence.hh>
#include <renderer/vulkan/semaphore.hh>

namespace brasio::renderer::vulkan
{
    class SyncObjects
    {
    public:
        SyncObjects(const VkDevice &logicalDevice, uint32_t semaphoreCount,
                    uint32_t fenceCount,
                    const VkSemaphoreCreateInfo &semaphoreCreateInfo,
                    const VkFenceCreateInfo &fenceCreateInfo);

        void waitSingleSemaphore(uint32_t index);
        void waitSemaphores(const std::vector<uint32_t> &indices);

        void waitSingleFence(uint32_t index);
        void waitFences(const std::vector<uint32_t> &indices);

        const VkSemaphore &semaphoreAt(uint32_t index) const;
        VkSemaphore &semaphoreAt(uint32_t index);

        const VkFence &fenceAt(uint32_t index) const;
        VkFence &fenceAt(uint32_t index);

        std::vector<VkFence>
        toFenceVector(const std::vector<uint32_t> &indices) const;

        void resetSingleFence(uint32_t index);
        void resetFences(const std::vector<uint32_t> &indices);

    private:
        VkDevice _logicalDevice;
        std::vector<Semaphore> _semaphores;
        std::vector<Fence> _fences;

        bool _checkSemaphoreBounds(uint32_t index) const;
        bool _checkFenceBounds(uint32_t index) const;
    };

    using SyncObjectsType = std::unique_ptr<SyncObjects>;
} // namespace brasio::renderer::vulkan
