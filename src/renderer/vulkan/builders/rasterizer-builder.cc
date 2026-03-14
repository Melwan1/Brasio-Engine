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
            .withFrontFace(VK_FRONT_FACE_CLOCKWISE)
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
} // namespace brasio::renderer::vulkan::builders
