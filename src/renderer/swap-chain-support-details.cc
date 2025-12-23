#include <renderer/swap-chain-support-details.hh>

bool SwapChainSupportDetails::isValid() const
{
    return !formats.empty() && !presentModes.empty();
}