#pragma once

#include <core/builder.hh>

#include <memory>
#include <vector>

#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

#include <renderer/vulkan/builders/application-info-builder.hh>
#include <renderer/vulkan/builders/debug-messenger-builder.hh>
#include <renderer/vulkan/instance.hh>

using InstanceType = std::unique_ptr<Instance>;

class InstanceBuilder : public Builder<InstanceType>
{
public:
    InstanceBuilder();

    virtual InstanceType build() override;
    virtual InstanceBuilder &base() override;
    virtual InstanceBuilder &
    withValidationLayers(std::vector<const char *> validationLayers = {});

private:
    ApplicationInfoBuilder _applicationBuilder;

    bool _enableValidationLayers;
    std::vector<const char *> _validationLayers;

    VkInstanceCreateInfo _instanceCreateInfo;

    uint32_t _instanceExtensionCount;
    std::vector<VkExtensionProperties> _instanceExtensions;

    std::unique_ptr<DebugMessengerBuilder> _debugMessengerBuilder;

    bool _checkValidationLayerSupport();
    std::vector<const char *> _getExtensions();
};
