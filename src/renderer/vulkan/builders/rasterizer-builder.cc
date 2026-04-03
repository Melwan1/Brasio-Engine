#include <renderer/vulkan/builders/rasterizer-builder.hh>
#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{
    RasterizerBuilder::RasterizerBuilder()
    {
        base();
    }

    RasterizerBuilder &RasterizerBuilder::base()
    {
        _structureType =
            VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        return withDepthClampEnable(VK_FALSE)
            .withDiscardEnable(VK_FALSE)
            .withPolygonMode(VK_POLYGON_MODE_FILL)
            .withLineWidth(1.0f)
            .withCullMode(VK_CULL_MODE_BACK_BIT)
            .withFrontFace(VK_FRONT_FACE_COUNTER_CLOCKWISE)
            .withDepthBiasEnable(VK_FALSE)
            .withDepthBiasConstantFactor(0.0f)
            .withDepthBiasClamp(0.0f)
            .withDepthBiasSlopeFactor(0.0);
    }

    VkPipelineRasterizationStateCreateInfo RasterizerBuilder::build()
    {
        VkPipelineRasterizationStateCreateInfo createInfo{};
        createInfo.sType = _structureType;
        createInfo.depthClampEnable = _depthClampEnable;
        createInfo.rasterizerDiscardEnable = _discardEnable;
        createInfo.polygonMode = _polygonMode;
        createInfo.lineWidth = _lineWidth;
        createInfo.cullMode = _cullMode;
        createInfo.frontFace = _frontFace;
        createInfo.depthBiasEnable = _depthBiasEnable;
        createInfo.depthBiasConstantFactor = _depthBiasConstantFactor;
        createInfo.depthBiasClamp = _depthBiasClamp;
        createInfo.depthBiasSlopeFactor = _depthBiasSlopeFactor;
        return createInfo;
    }

    RasterizerBuilder &
    RasterizerBuilder::withDepthClampEnable(const VkBool32 &depthClampEnable)
    {
        _depthClampEnable = depthClampEnable;
        return *this;
    }

    RasterizerBuilder &
    RasterizerBuilder::withDiscardEnable(const VkBool32 &discardEnable)
    {
        _discardEnable = discardEnable;
        return *this;
    }

    RasterizerBuilder &
    RasterizerBuilder::withPolygonMode(const VkPolygonMode &polygonMode)
    {
        _polygonMode = polygonMode;
        return *this;
    }

    RasterizerBuilder &RasterizerBuilder::withLineWidth(float lineWidth)
    {
        _lineWidth = lineWidth;
        return *this;
    }

    RasterizerBuilder &
    RasterizerBuilder::withCullMode(const VkCullModeFlags &cullMode)
    {
        _cullMode = cullMode;
        return *this;
    }

    RasterizerBuilder &
    RasterizerBuilder::withFrontFace(const VkFrontFace &frontFace)
    {
        _frontFace = frontFace;
        return *this;
    }

    RasterizerBuilder &
    RasterizerBuilder::withDepthBiasEnable(const VkBool32 &depthBiasEnable)
    {
        _depthBiasEnable = depthBiasEnable;
        return *this;
    }

    RasterizerBuilder &RasterizerBuilder::withDepthBiasConstantFactor(
        float depthBiasConstantFactor)
    {
        _depthBiasConstantFactor = depthBiasConstantFactor;
        return *this;
    }

    RasterizerBuilder &
    RasterizerBuilder::withDepthBiasClamp(float depthBiasClamp)
    {
        _depthBiasClamp = depthBiasClamp;
        return *this;
    }

    RasterizerBuilder &
    RasterizerBuilder::withDepthBiasSlopeFactor(float depthBiasSlopeFactor)
    {
        _depthBiasSlopeFactor = depthBiasSlopeFactor;
        return *this;
    }

    RasterizerBuilder &RasterizerBuilder::withConfig(const YAML::Node &config)
    {
        std::map<std::string, VkPolygonMode> polygonModeMap = {
            { "LINE", VK_POLYGON_MODE_LINE },
            { "FILL", VK_POLYGON_MODE_FILL },
        };
        std::map<std::string, VkCullModeFlags> cullModeMap = {
            { "FRONT", VK_CULL_MODE_FRONT_BIT },
            { "BACK", VK_CULL_MODE_BACK_BIT },
        };
        std::map<std::string, VkFrontFace> frontFaceMap = {
            { "CW", VK_FRONT_FACE_CLOCKWISE },
            { "CCW", VK_FRONT_FACE_COUNTER_CLOCKWISE },
        };
        return withDepthClampEnable(config["depth_clamp"].as<bool>())
            .withDiscardEnable(config["discard"].as<bool>())
            .withPolygonMode(
                polygonModeMap.at(config["polygon_mode"].as<std::string>()))
            .withLineWidth(config["line_width"].as<float>())
            .withCullMode(cullModeMap.at(config["cull_mode"].as<std::string>()))
            .withFrontFace(
                frontFaceMap.at(config["front_face"].as<std::string>()))
            .withDepthBiasEnable(config["depth_bias"].as<bool>())
            .withDepthBiasConstantFactor(
                config["depth_bias_constant_factor"].as<float>())
            .withDepthBiasClamp(config["depth_bias_clamp"].as<float>())
            .withDepthBiasSlopeFactor(
                config["depth_bias_slope_factor"].as<float>());
    }
} // namespace brasio::renderer::vulkan::builders
