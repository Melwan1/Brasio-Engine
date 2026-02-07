#pragma once

#include <core/builder.hh>
#include <renderer/vulkan/builders/application-info-builder.hh>

#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <vector>

using InstanceType = std::unique_ptr<VkInstance>;

class InstanceBuilder : public Builder<InstanceType>
{
public:
    InstanceBuilder();

    virtual InstanceType build() override;
    virtual InstanceBuilder &base() override;
    virtual InstanceBuilder &
    withValidationLayers(bool enable_validation_layers);

private:
    bool _enableValidationLayers;
    std::vector<const char *> _validationLayers;

    ApplicationInfoBuilder _application_builder;
    VkInstanceCreateInfo _instanceCreateInfo;

    bool checkValidationLayerSupport();
};
