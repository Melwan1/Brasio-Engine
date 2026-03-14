#include <renderer/vulkan/builders/descriptor-set-layout-builder.hh>

namespace brasio::renderer::vulkan::builders
{

    DescriptorSetLayoutBuilder::DescriptorSetLayoutBuilder(
        const VkDevice &logicalDevice)
        : _logicalDevice(logicalDevice)
    {
        base();
    }

    DescriptorSetLayoutBuilder &DescriptorSetLayoutBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        _bindings.clear();
        return *this;
    }

    DescriptorSetLayoutBuilder &DescriptorSetLayoutBuilder::withBindings(
        const std::vector<VkDescriptorSetLayoutBinding> &bindings)
    {
        _bindings = bindings;
        return *this;
    }

    DescriptorSetLayoutType DescriptorSetLayoutBuilder::build()
    {
        VkDescriptorSetLayoutCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.bindingCount = _bindings.size();
        createInfo.pBindings = _bindings.data();

        return std::make_unique<DescriptorSetLayout>(_logicalDevice,
                                                     createInfo);
    }

} // namespace brasio::renderer::vulkan::builders
