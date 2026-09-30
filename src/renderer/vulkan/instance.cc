#include <renderer/vulkan/instance.hh>

#include <renderer/vulkan/builders/debug-messenger-builder.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{
    Instance::Instance(const VulkanRenderer &renderer, const VkInstanceCreateInfo &createInfo)
        : Handler("instance",
                  [](const VkInstance &instance) { vkDestroyInstance(instance, nullptr); })
        , _renderer(renderer)
    {
        BRASIO_LOG_TRACE("Creating Vulkan instance", { "CREATE" });
        BRASIO_VULKAN_CHECK(vkCreateInstance(&createInfo, nullptr, &getHandle()),
                            "create Vulkan instance", { "CREATE" });
        BRASIO_LOG_TRACE("Created Vulkan instance", { "CREATE" });
        _debugMessenger = builders::DebugMessengerBuilder(getHandle()).build();
    }
} // namespace brasio::renderer::vulkan
