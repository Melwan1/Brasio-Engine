#include <renderer/vulkan/texture-sampler.hh>
#include <io/logging/logger.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{

    TextureSampler::TextureSampler(const LogicalDeviceType &logicalDevice,
                                   const VkSamplerCreateInfo &samplerInfo)
        : Handler("texture sampler",
                  [&logicalDevice](const VkSampler &sampler) {
                      vkDestroySampler(logicalDevice->getHandle(), sampler,
                                       nullptr);
                  })
    {
        BRASIO_LOG_TRACE("Creating texture sampler", { "CREATE" });

        BRASIO_VULKAN_CHECK(vkCreateSampler(logicalDevice->getHandle(),
                                            &samplerInfo, nullptr,
                                            &getHandle()),
                            "create texture sampler", { "CREATE" });
        BRASIO_LOG_TRACE("Created texture sampler", { "CREATE" });
    }

} // namespace brasio::renderer::vulkan
