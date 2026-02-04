#include <renderer/vulkan/builders/application-info-builder.hh>

ApplicationInfoBuilder::ApplicationInfoBuilder()
{
    base();
}

VkApplicationInfo ApplicationInfoBuilder::build()
{
    VkApplicationInfo applicationInfo{};
    applicationInfo.sType = this->_structure_type;
    applicationInfo.pApplicationName = this->_application_name.c_str();
    applicationInfo.applicationVersion = this->_application_version;
    applicationInfo.pEngineName = this->_engine_name.c_str();
    applicationInfo.engineVersion = this->_engine_version;
    applicationInfo.apiVersion = this->_api_version;
    applicationInfo.pNext = nullptr;

    return applicationInfo;
}

ApplicationInfoBuilder &ApplicationInfoBuilder::base()
{
    this->_structure_type = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    this->_application_name = "Brasio Engine";
    this->_application_version = VK_MAKE_VERSION(0, 1, 1);
    this->_engine_name = "Brasio Engine";
    this->_engine_version = VK_MAKE_VERSION(0, 1, 1);
    this->_api_version = VK_API_VERSION_1_3;

    return *this;
}
