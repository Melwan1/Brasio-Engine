#include <renderer/vulkan/instance.hh>

#include <renderer/vulkan/builders/debug-messenger-builder.hh>

#include <io/logging/logger.hh>

namespace brasio::renderer::vulkan
{
    Instance::Instance(const VkInstanceCreateInfo &createInfo)
        : Handler("instance", [](const VkInstance &instance) {
            vkDestroyInstance(instance, nullptr);
        })
    {
        BRASIO_LOG_TRACE("Creating Vulkan instance", { "CREATE" });
        if (vkCreateInstance(&createInfo, nullptr, &getHandle()) != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL("Could not create Vulkan instance",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE("Created Vulkan instance", { "CREATE" });
        _debugMessenger =
            builders::DebugMessengerBuilder().withInstance(getHandle()).build();
    }
} // namespace brasio::renderer::vulkan
