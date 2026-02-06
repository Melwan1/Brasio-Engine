#include <renderer/vulkan/builders/instance-builder.hh>

#include <vulkan/vulkan.hpp>
#include <vector>

#include <renderer/vulkan/builders/application-info-builder.hh>

InstanceBuilder::InstanceBuilder()
    : _instanceCreateInfo{}
{}

InstanceType InstanceBuilder::build()
{
    _instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    VkApplicationInfo applicationInfo = _application_builder.build();
    _instanceCreateInfo.pApplicationInfo = &applicationInfo;
    return nullptr;
}

InstanceBuilder &InstanceBuilder::base()
{
    _application_builder.base();
    _enableValidationLayers = false;
    return *this;
}

InstanceBuilder &
InstanceBuilder::withValidationLayers(bool enableValidationLayers)
{
    this->_enableValidationLayers = enableValidationLayers;
    if (this->_enableValidationLayers && !checkValidationLayerSupport())
    {
        throw std::runtime_error("Validation layers requested but not found.");
    }
    return *this;
}

bool InstanceBuilder::checkValidationLayerSupport()
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
