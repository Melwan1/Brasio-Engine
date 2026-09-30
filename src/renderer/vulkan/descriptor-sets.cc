#include <renderer/vulkan/descriptor-sets.hh>
#include <renderer/vulkan/vulkan-renderer.hh>
#include <utils/libutils.hh>

namespace brasio::renderer::vulkan
{

    DescriptorSets::DescriptorSets(const VulkanRenderer &renderer,
                                   const VkDescriptorSetAllocateInfo &allocateInfo)
        : Handler("descriptor sets",
                  [](const std::vector<VkDescriptorSet> &) {
                      BRASIO_LOG_TRACE("nothing to be done to destroy descriptor sets",
                                       { "DESTROY" });
                  })
        , _renderer(renderer)
    {
        BRASIO_LOG_TRACE("Allocating descriptor sets", { "CREATE" });
        getHandle().clear();
        getHandle().resize(allocateInfo.descriptorSetCount);
        BRASIO_VULKAN_CHECK(vkAllocateDescriptorSets(renderer.getLogicalDevice(), &allocateInfo,
                                                     getHandle().data()),
                            "allocate descriptor sets", { "CREATE" });
        BRASIO_LOG_TRACE("Allocated descriptor sets", { "CREATE" });
    }

    void DescriptorSets::update(const std::vector<BufferType> &uniformBuffers,
                                const std::vector<TextureType> &textures,
                                const std::vector<BufferType> &storageBuffers)
    {
        size_t uniformBuffersPerFrame = uniformBuffers.size() / getHandle().size();
        size_t storageBuffersPerFrame = storageBuffers.empty() ? 0 : 2;
        for (size_t i = 0; i < getHandle().size(); i++)
        {
            std::vector<VkWriteDescriptorSet> descriptorWrites{};
            descriptorWrites.resize(uniformBuffersPerFrame + textures.size()
                                    + storageBuffersPerFrame);

            std::vector<VkDescriptorBufferInfo> uniformBufferInfos;
            uniformBufferInfos.reserve(uniformBuffersPerFrame);
            std::vector<VkDescriptorImageInfo> textureInfos;
            textureInfos.reserve(textures.size());
            std::vector<VkDescriptorBufferInfo> storageBufferInfos;
            storageBufferInfos.reserve(storageBuffersPerFrame);

            for (size_t uniformIndex = 0; uniformIndex < uniformBuffersPerFrame; uniformIndex++)
            {
                size_t finalBufferIndex = i * uniformBuffersPerFrame + uniformIndex;
                VkDescriptorBufferInfo uniformBufferInfo{};
                uniformBufferInfo.buffer = uniformBuffers[finalBufferIndex]->getHandle();
                uniformBufferInfo.offset = 0;
                uniformBufferInfo.range = uniformBuffers[finalBufferIndex]->getSize();

                uniformBufferInfos.emplace_back(uniformBufferInfo);
                descriptorWrites[uniformIndex].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                descriptorWrites[uniformIndex].dstSet = getHandle().at(i);
                descriptorWrites[uniformIndex].dstBinding = uniformIndex;
                descriptorWrites[uniformIndex].dstArrayElement = 0;
                descriptorWrites[uniformIndex].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                descriptorWrites[uniformIndex].descriptorCount = 1;
                descriptorWrites[uniformIndex].pBufferInfo = &uniformBufferInfos.back();
                descriptorWrites[uniformIndex].pImageInfo = nullptr;
            }

            for (size_t textureIndex = 0; textureIndex < textures.size(); textureIndex++)
            {
                size_t descriptorTextureIndex = uniformBuffersPerFrame + textureIndex;
                VkDescriptorImageInfo textureInfo{};
                textureInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                textureInfo.imageView = textures[textureIndex]->getImageView();
                textureInfo.sampler = textures[textureIndex]->getTextureSampler()->getHandle();

                textureInfos.emplace_back(textureInfo);
                descriptorWrites[descriptorTextureIndex].sType =
                    VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                descriptorWrites[descriptorTextureIndex].dstSet = getHandle().at(i);
                descriptorWrites[descriptorTextureIndex].dstBinding = descriptorTextureIndex;
                descriptorWrites[descriptorTextureIndex].dstArrayElement = 0;
                descriptorWrites[descriptorTextureIndex].descriptorType =
                    VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                descriptorWrites[descriptorTextureIndex].descriptorCount = 1;
                descriptorWrites[descriptorTextureIndex].pBufferInfo = nullptr;
                descriptorWrites[descriptorTextureIndex].pImageInfo = &textureInfos.back();
            }

            for (size_t storageIndex = 0; storageIndex < storageBuffersPerFrame; storageIndex++)
            {
                bool evenFrame = (i % 2 == 0);
                size_t readBufferIndex = evenFrame ? 0 : 1;
                size_t writeBufferIndex = evenFrame ? 1 : 0;
                size_t finalBufferIndex = (storageIndex == 0) ? readBufferIndex : writeBufferIndex;
                VkDescriptorBufferInfo storageBufferInfo{};
                storageBufferInfo.buffer = storageBuffers[finalBufferIndex]->getHandle();
                storageBufferInfo.offset = 0;
                storageBufferInfo.range = storageBuffers[finalBufferIndex]->getSize();

                storageBufferInfos.emplace_back(storageBufferInfo);
                size_t descriptorStorageIndex =
                    uniformBuffersPerFrame + textures.size() + storageIndex;
                descriptorWrites[descriptorStorageIndex].sType =
                    VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                descriptorWrites[descriptorStorageIndex].dstSet = getHandle().at(i);
                descriptorWrites[descriptorStorageIndex].dstBinding = descriptorStorageIndex;
                descriptorWrites[descriptorStorageIndex].dstArrayElement = 0;
                descriptorWrites[descriptorStorageIndex].descriptorType =
                    VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
                descriptorWrites[descriptorStorageIndex].descriptorCount = 1;
                descriptorWrites[descriptorStorageIndex].pBufferInfo = &storageBufferInfos.back();
                descriptorWrites[descriptorStorageIndex].pImageInfo = nullptr;
            }

            vkUpdateDescriptorSets(_renderer.getLogicalDevice(),
                                   static_cast<uint32_t>(descriptorWrites.size()),
                                   descriptorWrites.data(), 0, nullptr);
        }
    }
} // namespace brasio::renderer::vulkan
