#include <renderer/vulkan/builders/graphics-pipeline-builder.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{
    GraphicsPipelineBuilder::GraphicsPipelineBuilder(
        const VkDevice &logicalDevice,
        const shaders::ShaderManager &shaderManager,
        const VkPipelineLayout &pipelineLayout, const VkRenderPass &renderPass)
        : _logicalDevice(logicalDevice)
        , _shaderManager(shaderManager)
        , _pipelineLayout(pipelineLayout)
        , _renderPass(renderPass)
        , _pipelineLayoutBuilder(logicalDevice)
    {
        base();
    }

    GraphicsPipelineBuilder &GraphicsPipelineBuilder::base()
    {
        _structureType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

        _dynamicStateBuilder.base();
        _vertexInputBuilder.base();
        _inputAssemblyBuilder.base();
        _viewportStateBuilder.base();
        _rasterizerBuilder.base();
        _multisamplingBuilder.base();
        _colorBlendAttachmentBuilder.base();
        _colorBlendStateBuilder.base();
        _pipelineLayoutBuilder.base();

        _shaderBuilders.clear();
        _shaderInfos.clear();

        return *this;
    }

    GraphicsPipelineBuilder &GraphicsPipelineBuilder::withShaders(
        const std::vector<fs::path> &shaderPaths)
    {
        _shaderBuilders.clear();
        _shaderInfos.clear();
        for (unsigned index = 0; index < shaderPaths.size(); index++)
        {
            _shaderBuilders.emplace_back(_logicalDevice, _shaderManager);
            _shaderBuilders.back().withShader(shaderPaths.at(index));
            _shaderInfos.emplace_back(_shaderBuilders.back().build());
        }
        _shaderPaths = shaderPaths;
        _checkUniqueShaderType(".vert");
        _checkUniqueShaderType(".frag");
        return *this;
    }

    GraphicsPipelineBuilder &
    GraphicsPipelineBuilder::withConfig(const YAML::Node &config)
    {
        _dynamicStateBuilder.withConfig(config["dynamic_states"]);
        _inputAssemblyBuilder.withConfig(config["input_assembly"]);
        _rasterizerBuilder.withConfig(config["rasterizer"]);
        _multisamplingBuilder.withConfig(config["multisampling"]);
        _colorBlendAttachmentBuilder.withConfig(
            config["color_blend_attachment"]);
        _colorBlendStateBuilder.withConfig(config["color_blend_state"]);

        std::vector<fs::path> shaders = {
            config["shaders"]["vertex"].as<std::string>(),
            config["shaders"]["fragment"].as<std::string>()
        };
        return withShaders(shaders);
    }

    GraphicsPipelineType GraphicsPipelineBuilder::build()
    {
        VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo =
            _dynamicStateBuilder.build();
        VkPipelineVertexInputStateCreateInfo vertexInputCreateInfo =
            _vertexInputBuilder.build();
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyCreateInfo =
            _inputAssemblyBuilder.build();
        VkPipelineViewportStateCreateInfo viewportStateCreateInfo =
            _viewportStateBuilder.build();
        VkPipelineRasterizationStateCreateInfo rasterizerCreateInfo =
            _rasterizerBuilder.build();
        VkPipelineMultisampleStateCreateInfo multisamplingCreateInfo =
            _multisamplingBuilder.build();
        VkPipelineColorBlendAttachmentState colorBlendAttachment =
            _colorBlendAttachmentBuilder.build();
        VkPipelineColorBlendStateCreateInfo colorBlending =
            _colorBlendStateBuilder
                .withColorBlendAttachments({ colorBlendAttachment })
                .build();

        VkGraphicsPipelineCreateInfo pipelineCreateInfo{};
        pipelineCreateInfo.sType = _structureType;
        pipelineCreateInfo.stageCount = _shaderInfos.size();
        pipelineCreateInfo.pStages = _shaderInfos.data();

        pipelineCreateInfo.pVertexInputState = &vertexInputCreateInfo;
        pipelineCreateInfo.pInputAssemblyState = &inputAssemblyCreateInfo;
        pipelineCreateInfo.pViewportState = &viewportStateCreateInfo;
        pipelineCreateInfo.pRasterizationState = &rasterizerCreateInfo;
        pipelineCreateInfo.pMultisampleState = &multisamplingCreateInfo;
        pipelineCreateInfo.pColorBlendState = &colorBlending;
        pipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;
        pipelineCreateInfo.pDepthStencilState = nullptr;

        pipelineCreateInfo.layout = _pipelineLayout;
        pipelineCreateInfo.renderPass = _renderPass;
        pipelineCreateInfo.subpass = 0;
        pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
        pipelineCreateInfo.basePipelineIndex = -1;

        return std::make_unique<GraphicsPipeline>(_logicalDevice,
                                                  pipelineCreateInfo);
    }
    bool GraphicsPipelineBuilder::_checkUniqueShaderType(
        const std::string &extension)
    {
        std::ostringstream check_message_oss;
        check_message_oss << "Checking " << extension << " against "
                          << _shaderPaths.size() << " shaders.";
        io::logging::Logger::debug(std::cout, check_message_oss.str());
        int shaderCount = std::count_if(
            _shaderPaths.begin(), _shaderPaths.end(),
            [&extension](const fs::path &shaderPath) {
                io::logging::Logger::trace(
                    std::cout,
                    "shader path: " + shaderPath.string()
                        + ", extension: " + shaderPath.extension().string());
                return shaderPath.extension().string() == extension;
            });
        io::logging::Logger::trace(std::cout,
                                   "Found " + std::to_string(shaderCount)
                                       + " shaders with the " + extension
                                       + " extension in the graphics pipeline",
                                   { "CREATE" });
        bool res = shaderCount == 1;
        if (!res)
        {
            io::logging::Logger::error(std::cout,
                                       "Should have exactly 1 shader with the "
                                           + extension + " extension",
                                       { "CREATE" });
        }
        return res;
    }
} // namespace brasio::renderer::vulkan::builders
