#include <renderer/vulkan/texture-sampler.hh>
#include "io/logging/logger.hh"

namespace brasio::renderer::vulkan {

    TextureSampler::TextureSampler(const LogicalDeviceType &logicalDevice, const VkSamplerCreateInfo &samplerInfo)
        : Handler("texture sampler", [&logicalDevice](const VkSampler &sampler) { vkDestroySampler(logicalDevice->getHandle(), sampler, nullptr); })
    {
        BRASIO_LOG_TRACE("Creating texture sampler", { "CREATE" });
        
        if (vkCreateSampler(logicalDevice->getHandle(), &samplerInfo, nullptr, &getHandle()) != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL("Could not create texture sampler", { "CREATE" });
        }
        BRASIO_LOG_TRACE("Created texture sampler", { "CREATE" });
    }

}
