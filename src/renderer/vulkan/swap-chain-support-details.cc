#include <renderer/vulkan/swap-chain-support-details.hh>

namespace brasio::renderer::vulkan
{
    bool SwapChainSupportDetails::isValid() const
    {
        return !formats.empty() && !presentModes.empty();
    }
} // namespace brasio::renderer::vulkan
