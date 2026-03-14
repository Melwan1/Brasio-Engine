#include <renderer/vulkan/pipeline-layout.hh>

namespace brasio::renderer::vulkan
{
    PipelineLayout::PipelineLayout(const VkDevice &logicalDevice,
                                   const VkPipelineLayoutCreateInfo &createInfo)
        : Handler("pipeline layout",
                  [logicalDevice](const VkPipelineLayout &pipelineLayout) {
                      vkDestroyPipelineLayout(logicalDevice, pipelineLayout,
                                              nullptr);
                  })
    {
        io::logging::Logger::trace(std::cout, "Creating pipeline layout",
                                   { "CREATE" });
        if (vkCreatePipelineLayout(logicalDevice, &createInfo, nullptr,
                                   &getHandle())
            != VK_SUCCESS)
        {
            io::logging::Logger::critical(
                std::cout, "Could not create pipelineLayout", { "CREATE" });
        }

        io::logging::Logger::trace(std::cout, "Created pipeline layout");
    }
} // namespace brasio::renderer::vulkan
