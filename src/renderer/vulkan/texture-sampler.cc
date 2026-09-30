#include <renderer/vulkan/texture-sampler.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{

    TextureSampler::TextureSampler(const VulkanRenderer &renderer,
                                   const VkSamplerCreateInfo &samplerInfo)
        : Handler("texture sampler", [&renderer](const VkSampler &sampler) {
            vkDestroySampler(renderer.getLogicalDevice(), sampler, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating texture sampler", { "CREATE" });

        BRASIO_VULKAN_CHECK(
            vkCreateSampler(renderer.getLogicalDevice(), &samplerInfo, nullptr, &getHandle()),
            "create texture sampler", { "CREATE" });
        BRASIO_LOG_TRACE("Created texture sampler", { "CREATE" });
    }

} // namespace brasio::renderer::vulkan
