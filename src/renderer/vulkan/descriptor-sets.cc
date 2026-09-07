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

    void DescriptorSets::update(const std::vector<BufferType> &buffers, const ImageType &textureImageView, const TextureSamplerType &textureSampler)
    {
        for (size_t i = 0; i < getHandle().size(); i++)
        {
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = buffers[i]->getHandle();
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(structs::UniformBufferObject);

            VkDescriptorImageInfo imageInfo{};
            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            imageInfo.imageView = textureImageView->getHandle();
            imageInfo.sampler = textureSampler->getHandle();

            std::array<VkWriteDescriptorSet, 2> descriptorWrites{};
            descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[0].dstSet = getHandle().at(i);
            descriptorWrites[0].dstBinding = 0;
            descriptorWrites[0].dstArrayElement = 0;
            descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrites[0].descriptorCount = 1;
            descriptorWrites[0].pBufferInfo = &bufferInfo;
            descriptorWrites[0].pImageInfo = nullptr;

            descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[1].dstSet = getHandle().at(i);
            descriptorWrites[1].dstBinding = 1;
            descriptorWrites[1].dstArrayElement = 0;
            descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            descriptorWrites[1].descriptorCount = 1;
            descriptorWrites[1].pBufferInfo = nullptr;
            descriptorWrites[1].pImageInfo = &imageInfo;


            vkUpdateDescriptorSets(_logicalDevice, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0,
                                   nullptr);
        }
    }
} // namespace brasio::renderer::vulkan
