#pragma once

#include <core/builder.hh>

#include <vulkan/vulkan_core.h>

namespace brasio::renderer::vulkan::builders
{
    class RasterizerBuilder
        : public core::Builder<VkPipelineRasterizationStateCreateInfo>
    {
    public:
        RasterizerBuilder();

        virtual RasterizerBuilder &base() override;
        virtual VkPipelineRasterizationStateCreateInfo build() override;

        RasterizerBuilder &withDepthClampEnable(const VkBool32 &enabled);
        RasterizerBuilder &withDiscardEnable(const VkBool32 &enabled);
        RasterizerBuilder &withPolygonMode(const VkPolygonMode &polygonMode);
        RasterizerBuilder &withLineWidth(float lineWidth);
        RasterizerBuilder &withCullMode(const VkCullModeFlags &cullMode);
        RasterizerBuilder &withFrontFace(const VkFrontFace &frontFace);
        RasterizerBuilder &withDepthBiasEnable(const VkBool32 &enabled);
        RasterizerBuilder &
        withDepthBiasConstantFactor(float depthBiasConstantFactor);
        RasterizerBuilder &withDepthBiasClamp(float depthBiasClamp);
        RasterizerBuilder &withDepthBiasSlopeFactor(float depthBiasSlopeFactor);

    private:
        VkStructureType _structureType;

        VkBool32 _depthClampEnable;
        VkBool32 _discardEnable;
        VkPolygonMode _polygonMode;
        float _lineWidth;
        VkCullModeFlags _cullMode;
        VkFrontFace _frontFace;
        VkBool32 _depthBiasEnable;
        float _depthBiasConstantFactor;
        float _depthBiasClamp;
        float _depthBiasSlopeFactor;
    };
} // namespace brasio::renderer::vulkan::builders
