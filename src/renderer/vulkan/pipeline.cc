#include <renderer/vulkan/pipeline.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::renderer::vulkan
{
    Pipeline::Pipeline(const VulkanRenderer &renderer, PipelineLayoutType pipelineLayout)
        : Handler("pipeline",
                  [&renderer](const VkPipeline &pipeline) {
                      vkDestroyPipeline(renderer.getLogicalDevice(), pipeline, nullptr);
                  })
        , _renderer(renderer)
        , _pipelineLayout(std::move(pipelineLayout))
    {}

    const PipelineLayout &Pipeline::getPipelineLayout() const
    {
        return *_pipelineLayout;
    }
} // namespace brasio::renderer::vulkan
