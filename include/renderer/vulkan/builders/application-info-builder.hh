#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>
#include <string>

class ApplicationInfoBuilder : public Builder<VkApplicationInfo>
{
public:
    ApplicationInfoBuilder();

    virtual VkApplicationInfo build() override;
    virtual ApplicationInfoBuilder &base() override;

private:
    VkStructureType _structure_type;
    std::string _application_name;
    uint32_t _application_version;
    std::string _engine_name;
    uint32_t _engine_version;
    uint32_t _api_version;
};
