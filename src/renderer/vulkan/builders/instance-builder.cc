#include <renderer/vulkan/builders/instance-builder.hh>

#include <iostream>

#include <vulkan/vulkan.hpp>

#include <io/logging/logger.hh>
#include <renderer/vulkan/builders/application-info-builder.hh>
#include <renderer/vulkan/instance.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{
    InstanceBuilder::InstanceBuilder()
        : _applicationBuilder{}
        , _enableValidationLayers(false)
        , _validationLayers{}
        , _instanceCreateInfo{}
    {}

    InstanceType InstanceBuilder::build()
    {
        _instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        VkApplicationInfo applicationInfo = _applicationBuilder.build();
        _instanceCreateInfo.pApplicationInfo = &applicationInfo;

        std::vector<const char *> extensions = _getExtensions();
        _instanceCreateInfo.enabledExtensionCount = extensions.size();
        _instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

        vkEnumerateInstanceExtensionProperties(
            nullptr, &_instanceExtensionCount, nullptr);
        _instanceExtensions.resize(_instanceExtensionCount);
        vkEnumerateInstanceExtensionProperties(
            nullptr, &_instanceExtensionCount, _instanceExtensions.data());

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo =
            DebugMessengerBuilder().getCreateInfo();

        if (_enableValidationLayers)
        {
            _instanceCreateInfo.enabledLayerCount =
                static_cast<uint32_t>(_validationLayers.size());
            _instanceCreateInfo.ppEnabledLayerNames = _validationLayers.data();

            _instanceCreateInfo.pNext = &debugCreateInfo;
        }
        else
        {
            _instanceCreateInfo.enabledLayerCount = 0;

            _instanceCreateInfo.pNext = nullptr;
        }

        std::unique_ptr<VkInstance> instance = std::make_unique<VkInstance>();

        return std::make_unique<Instance>(_instanceCreateInfo);
    }

    InstanceBuilder &InstanceBuilder::base()
    {
        _applicationBuilder.base();
        _enableValidationLayers = false;
        return *this;
    }

    InstanceBuilder &InstanceBuilder::withValidationLayers(
        std::vector<const char *> validationLayers)
    {
        bool enableValidationLayers = !validationLayers.empty();
        this->_enableValidationLayers = enableValidationLayers;
        if (this->_enableValidationLayers && !_checkValidationLayerSupport())
        {
            BRASIO_LOG_ERROR(std::cout,
                             "Validation layers requested but not found",
                             { "DEBUGGING" });
        }
        this->_validationLayers = validationLayers;
        return *this;
    }

    std::vector<const char *> InstanceBuilder::_getExtensions()
    {
        uint32_t extensionCount = 0;
        const char **glfwExtensions =
            glfwGetRequiredInstanceExtensions(&extensionCount);
        std::vector<const char *> extensions(glfwExtensions,
                                             glfwExtensions + extensionCount);
        if (_enableValidationLayers)
        {
            extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        return extensions;
    }

    bool InstanceBuilder::_checkValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        _validationLayers.clear();
        _validationLayers.emplace_back("VK_LAYER_KHRONOS_validation");

        for (auto &layerName : _validationLayers)
        {
            if (std::find_if(availableLayers.begin(), availableLayers.end(),
                             [&layerName](VkLayerProperties &prop) {
                                 return !std::strcmp(prop.layerName, layerName);
                             })
                == availableLayers.end())
            {
                return false;
            }
        }
        return true;
    }
} // namespace brasio::renderer::vulkan::builders
