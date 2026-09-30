#include <renderer/vulkan/builders/logical-device-builder.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

#include <set>

namespace brasio::renderer::vulkan::builders
{
    LogicalDeviceBuilder::LogicalDeviceBuilder(const VulkanRenderer &renderer)
        : _renderer(renderer)
        , _queuePriority(1.0f)
    {
        base();
    }

    LogicalDeviceBuilder &LogicalDeviceBuilder::base()
    {
        _indices = _renderer.getPhysicalDeviceWrapper().findQueueFamilies();
        std::set<uint32_t> uniqueQueueFamilies = { _indices.graphicsComputeFamily.value(),
                                                   _indices.presentFamily.value() };
        for (const uint32_t queueFamilyIndex : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &_queuePriority;
            _queueCreateInfos.emplace_back(queueCreateInfo);
        }
        return *this;
    }

    LogicalDeviceType LogicalDeviceBuilder::build()
    {
        VkPhysicalDeviceFeatures deviceFeatures{};
        deviceFeatures.samplerAnisotropy = VK_TRUE;
        deviceFeatures.fillModeNonSolid = VK_TRUE;
        deviceFeatures.wideLines = VK_TRUE;
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = _queueCreateInfos.data();
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(_queueCreateInfos.size());
        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(
            _renderer.getPhysicalDeviceWrapper().getDeviceExtensions().size());
        createInfo.ppEnabledExtensionNames =
            _renderer.getPhysicalDeviceWrapper().getDeviceExtensions().data();

        /* if (_validationLayers.empty())
         {
             createInfo.enabledLayerCount = 0;
         }
         else
         {
             createInfo.enabledLayerCount =
                 static_cast<uint32_t>(_validationLayers.size());
             createInfo.ppEnabledLayerNames = _validationLayers.data();
         }
         */ // FIXME
        createInfo.enabledLayerCount = 0;

        return std::make_unique<LogicalDevice>(_renderer, createInfo, _indices);
    }
} // namespace brasio::renderer::vulkan::builders
