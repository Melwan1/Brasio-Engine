#include <renderer/vulkan/pipeline-manager.hh>

namespace brasio::renderer::vulkan
{
    PipelineManager::PipelineManager(const VulkanRenderer &renderer)
        : _renderer(renderer)
    {}

    PipelineType PipelineManager::createObject(const YAML::Node &config)
    {
        builders::DescriptorSetLayoutBindingBuilder::resetIndex();
        if (!config["type"].as<std::string>().compare("GRAPHICS"))
        {
            builders::GraphicsPipelineBuilder pipelineBuilder(_renderer);
            pipelineBuilder.withDescriptorSetLayout(builders::DescriptorSetLayoutBuilder(_renderer)
                                                        .withUniformBuffers(1)
                                                        .withTextures(1)
                                                        .build());
            pipelineBuilder.withConfig(config);
            return pipelineBuilder.build();
        }
        if (!config["type"].as<std::string>().compare("COMPUTE"))
        {
            PipelineLayoutType pipelineLayout =
                builders::PipelineLayoutBuilder(_renderer)
                    .withDescriptorSetLayout(builders::DescriptorSetLayoutBuilder(_renderer)
                                                 .withUniformBuffers(1, VK_SHADER_STAGE_COMPUTE_BIT)
                                                 .withStorageBuffers(2)
                                                 .build())
                    .build();
            return builders::ComputePipelineBuilder(_renderer)
                .withShader("compute/particles.comp")
                .withPipelineLayout(std::move(pipelineLayout))
                .build();
        }
        BRASIO_LOG_CRITICAL("Pipeline config for id " + config["id"].as<std::string>()
                                + " must be of type GRAPHICS or COMPUTE",
                            { "CREATE", "PIPELINE" });
        return nullptr;
    }
} // namespace brasio::renderer::vulkan
