#include <renderer/vulkan/descriptor-sets.hh>

#include <renderer/structs/uniform-buffer-object.hh>

namespace brasio::renderer::vulkan
{

    DescriptorSets::DescriptorSets(
        const VkDevice &logicalDevice,
        const VkDescriptorSetAllocateInfo &allocateInfo)
        : Handler("descriptor sets",
                  [](const std::vector<VkDescriptorSet> &) {
                      BRASIO_LOG_TRACE(
                          "nothing to be done to destroy descriptor sets",
                          { "DESTROY" });
                  })
        , _logicalDevice(logicalDevice)
    {
        BRASIO_LOG_TRACE("Allocating descriptor sets", { "CREATE" });
        getHandle().clear();
        getHandle().resize(allocateInfo.descriptorSetCount);
        if (vkAllocateDescriptorSets(logicalDevice, &allocateInfo,
                                     getHandle().data())
            != VK_SUCCESS)
        {
            BRASIO_LOG_CRITICAL("Could not allocate descriptor sets",
                                { "CREATE" });
        }
        BRASIO_LOG_TRACE("Allocated descriptor sets", { "CREATE" });
    }

    void DescriptorSets::update(const std::vector<BufferType> &buffers)
    {
        for (size_t i = 0; i < getHandle().size(); i++)
        {
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = buffers[i]->getHandle();
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(structs::UniformBufferObject);

            VkWriteDescriptorSet descriptorWrite{};
            descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite.dstSet = getHandle().at(i);
            descriptorWrite.dstBinding = 0;
            descriptorWrite.dstArrayElement = 0;
            descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrite.descriptorCount = 1;
            descriptorWrite.pBufferInfo = &bufferInfo;
            descriptorWrite.pImageInfo = nullptr;
            descriptorWrite.pTexelBufferView = nullptr;
            vkUpdateDescriptorSets(_logicalDevice, 1, &descriptorWrite, 0,
                                   nullptr);
        }
    }
} // namespace brasio::renderer::vulkan
