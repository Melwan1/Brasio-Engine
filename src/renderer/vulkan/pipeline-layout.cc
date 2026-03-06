#include <renderer/vulkan/pipeline-layout.hh>

PipelineLayout::PipelineLayout(const VkDevice &logicalDevice,
                               const VkPipelineLayoutCreateInfo &createInfo)
    : Handler("pipeline layout",
              [logicalDevice](const VkPipelineLayout &pipelineLayout) {
                  vkDestroyPipelineLayout(logicalDevice, pipelineLayout,
                                          nullptr);
              })
{
    Logger::trace(std::cout, "Creating pipeline layout", { "CREATE" });
    if (vkCreatePipelineLayout(logicalDevice, &createInfo, nullptr,
                               &getHandle())
        != VK_SUCCESS)
    {
        Logger::critical(std::cout, "Could not create pipelineLayout",
                         { "CREATE" });
    }

    Logger::trace(std::cout, "Created pipeline layout");
}
