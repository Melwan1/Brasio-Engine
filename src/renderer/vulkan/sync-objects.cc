#include <renderer/vulkan/sync-objects.hh>

#include <io/logging/logger.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan
{
    SyncObjects::SyncObjects(const VkDevice &logicalDevice,
                             uint32_t semaphoreCount, uint32_t fenceCount,
                             const VkSemaphoreCreateInfo &semaphoreCreateInfo,
                             const VkFenceCreateInfo &fenceCreateInfo)
        : _logicalDevice(logicalDevice)
    {
        _semaphores.reserve(semaphoreCount);
        _fences.reserve(semaphoreCount);
        for (uint32_t semaphoreIndex = 0; semaphoreIndex < semaphoreCount;
             semaphoreIndex++)
        {
            _semaphores.emplace_back(_logicalDevice, semaphoreCreateInfo);
        }
        for (uint32_t fenceIndex = 0; fenceIndex < fenceCount; fenceIndex++)
        {
            _fences.emplace_back(_logicalDevice, fenceCreateInfo);
        }
    }

    void SyncObjects::waitSingleSemaphore(uint32_t index)
    {
        waitSemaphores({ index });
    }

    void SyncObjects::waitSemaphores(const std::vector<uint32_t> &indices)
    {
        for (uint32_t index : indices)
        {
            _checkSemaphoreBounds(index);
        }
        io::logging::Logger::info(std::cout,
                                  "Nothing to be done for semaphores");
    }

    void SyncObjects::waitSingleFence(uint32_t index)
    {
        waitFences({ index });
    }

    void SyncObjects::waitFences(const std::vector<uint32_t> &indices)
    {
        std::vector<VkFence> fencesToWait = toFenceVector(indices);
        vkWaitForFences(_logicalDevice, indices.size(), fencesToWait.data(),
                        VK_TRUE, UINT64_MAX);
    }

    const VkSemaphore &SyncObjects::semaphoreAt(uint32_t index) const
    {
        _checkSemaphoreBounds(index);
        return _semaphores[index].getHandle();
    }

    VkSemaphore &SyncObjects::semaphoreAt(uint32_t index)
    {
        _checkSemaphoreBounds(index);
        return _semaphores[index].getHandle();
    }

    const VkFence &SyncObjects::fenceAt(uint32_t index) const
    {
        _checkFenceBounds(index);
        return _fences[index].getHandle();
    }

    VkFence &SyncObjects::fenceAt(uint32_t index)
    {
        _checkFenceBounds(index);
        return _fences[index].getHandle();
    }

    std::vector<VkFence>
    SyncObjects::toFenceVector(const std::vector<uint32_t> &indices) const
    {
        std::vector<uint32_t> newIndices = indices;

        // if no indices are provided, all fences are to be put in the fence
        // vector
        if (indices.empty())
        {
            for (uint32_t index = 0; index < _fences.size(); index++)
            {
                newIndices.emplace_back(index);
            }
        }
        std::vector<VkFence> fencesToWait;
        fencesToWait.reserve(_fences.size());
        for (uint32_t index : newIndices)
        {
            if (!_checkFenceBounds(index))
            {
                fencesToWait.emplace_back(_fences[index].getHandle());
            }
        }
        return fencesToWait;
    }

    void SyncObjects::resetSingleFence(uint32_t index)
    {
        resetFences({ index });
    }

    void SyncObjects::resetFences(const std::vector<uint32_t> &indices)
    {
        std::vector<VkFence> fencesToWait = toFenceVector(indices);
        vkResetFences(_logicalDevice, fencesToWait.size(), fencesToWait.data());
    }

    bool SyncObjects::_checkSemaphoreBounds(uint32_t index) const
    {
        if (index >= _semaphores.size())
        {
            std::ostringstream oss;
            oss << "Semaphore at index " << index
                << " is out of bounds for vector of size "
                << _semaphores.size();
            io::logging::Logger::warning(std::cout, oss.str());
            return true;
        }
        return false;
    }

    bool SyncObjects::_checkFenceBounds(uint32_t index) const
    {
        if (index >= _semaphores.size())
        {
            std::ostringstream oss;
            oss << "Fence at index " << index
                << " is out of bounds for vector of size " << _fences.size();
            io::logging::Logger::warning(std::cout, oss.str());
            return true;
        }
        return false;
    }
} // namespace brasio::renderer::vulkan
