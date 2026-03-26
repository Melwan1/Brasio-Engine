#pragma once

#include <glm/glm.hpp>
#include <renderer/renderer.hh>

#include <geometry/vertex.hh>
#include <mesh/transform-mode.hh>

#include <renderer/vulkan/buffer.hh>
#include <renderer/vulkan/command-pool.hh>
#include <renderer/vulkan/vulkan-renderer.hh>

namespace brasio::renderer::vulkan
{

    class VulkanRenderer;

}

namespace brasio::mesh
{

    class Mesh
    {
    public:
        Mesh(const std::vector<geometry::Vertex> &vertices,
             const std::vector<uint16_t> &indices);
        Mesh(const std::pair<std::vector<geometry::Vertex>,
                             std::vector<uint16_t>> &vertices_indices);

        const std::vector<geometry::Vertex> &getVertices() const;
        std::vector<geometry::Vertex> &getVertices();

        const std::vector<uint16_t> &getIndices() const;
        std::vector<uint16_t> &getIndices();

        const renderer::vulkan::BufferType &getVertexBuffer() const;
        renderer::vulkan::BufferType &getVertexBuffer();

        const renderer::vulkan::BufferType &getIndexBuffer() const;
        renderer::vulkan::BufferType &getIndexBuffer();

        void draw(const VkCommandBuffer &commandBuffer,
                  const renderer::vulkan::VulkanRenderer &renderer) const;
        void
        drawWireframe(const VkCommandBuffer &commandBuffer,
                      const renderer::vulkan::VulkanRenderer &renderer) const;

        void applyTransform(TransformMode transformMode,
                            const glm::mat4 &transform);

        void applyRotate(TransformMode transformMode,
                         const glm::vec3 &eulerAngles);

        void applyTranslation(TransformMode transformMode,
                              const glm::vec3 &translation);

        void applyScale(TransformMode transformMode, const glm::vec3 &scale);

        void createVertexBuffer(
            const renderer::vulkan::PhysicalDeviceType &physicalDevice,
            const renderer::vulkan::LogicalDeviceType &logicalDevice,
            const renderer::vulkan::CommandPoolType &commandPool);

        void createIndexBuffer(
            const renderer::vulkan::PhysicalDeviceType &physicalDevice,
            const renderer::vulkan::LogicalDeviceType &logicalDevice,
            const renderer::vulkan::CommandPoolType &commandPool);

        void createBuffers(
            const renderer::vulkan::PhysicalDeviceType &physicalDevice,
            const renderer::vulkan::LogicalDeviceType &logicalDevice,
            const renderer::vulkan::CommandPoolType &commandPool);

    private:
        std::vector<geometry::Vertex> _vertices;
        std::vector<uint16_t> _indices;

        renderer::vulkan::BufferType _vertexBuffer;
        renderer::vulkan::BufferType _indexBuffer;

        glm::mat4 _transformGPU;
        glm::mat4 _transformCPU;
    };

    using MeshType = std::unique_ptr<Mesh>;

} // namespace brasio::mesh
