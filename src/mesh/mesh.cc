#include <mesh/mesh.hh>

#include <glm/gtx/transform.hpp>

#include <renderer/vulkan/builders/buffer-builder.hh>
#include <io/logging/logger.hh>

namespace brasio::mesh
{

    Mesh::Mesh(const std::vector<geometry::Vertex> &vertices, const std::vector<IndexType> &indices)
        : _vertices(vertices)
        , _indices(indices)
    {}

    Mesh::Mesh(
        const std::pair<std::vector<geometry::Vertex>, std::vector<IndexType>> &vertices_indices)
        : Mesh(vertices_indices.first, vertices_indices.second)
    {}

    const std::vector<geometry::Vertex> &Mesh::getVertices() const
    {
        return _vertices;
    }

    std::vector<geometry::Vertex> &Mesh::getVertices()
    {
        return _vertices;
    }

    const std::vector<Mesh::IndexType> &Mesh::getIndices() const
    {
        return _indices;
    }

    const renderer::vulkan::BufferType &Mesh::getVertexBuffer() const
    {
        return _vertexBuffer;
    }

    renderer::vulkan::BufferType &Mesh::getVertexBuffer()
    {
        return _vertexBuffer;
    }

    const renderer::vulkan::BufferType &Mesh::getIndexBuffer() const
    {
        return _indexBuffer;
    }

    renderer::vulkan::BufferType &Mesh::getIndexBuffer()
    {
        return _indexBuffer;
    }

    std::vector<Mesh::IndexType> &Mesh::getIndices()
    {
        return _indices;
    }

    void Mesh::draw(const VkCommandBuffer &commandBuffer,
                    const renderer::vulkan::VulkanRenderer &renderer) const
    {
        VkBuffer vertexBuffers[] = { getVertexBuffer()->getHandle() };
        VkDeviceSize offsets[] = { 0 };
        uint32_t firstBinding = 0;
        uint32_t bindingCount = 1;
        vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(commandBuffer, getIndexBuffer()->getHandle(), 0, VK_INDEX_TYPE_UINT32);
        vkCmdBindDescriptorSets(
            commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
            renderer.getGraphicsPipelines().at(0)->getPipelineLayout().getHandle(), 0, 1,
            &renderer.getDescriptorSets().getHandle().at(renderer.getCurrentFrame()), 0, nullptr);
        uint32_t instanceCount = 1;
        uint32_t firstVertex = 0;
        uint32_t firstInstance = 0;
        uint32_t instanceOffset = 0;
        vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(getIndices().size()), instanceCount,
                         firstVertex, firstInstance, instanceOffset);
    }
    void Mesh::drawWireframe(const VkCommandBuffer &commandBuffer,
                             const renderer::vulkan::VulkanRenderer &renderer) const
    {
        (void)commandBuffer;
        (void)renderer;
    }

    void Mesh::applyTransform(TransformMode transformMode, const glm::mat4 &transform)
    {
        if (transformMode == TransformMode::CPU)
        {
            for (auto &vertex : _vertices)
            {
                vertex.position = glm::vec3(transform * glm::vec4(vertex.position, 1.0));
            }
        }
        else
        {
            _transformGPU = transform * _transformGPU;
        }
    }

    void Mesh::applyRotate(TransformMode transformMode, const glm::vec3 &eulerAngles)
    {
        glm::mat4 transform = glm::mat4(1.0);
        transform = glm::rotate(transform, eulerAngles[1], glm::vec3(0.0, 1.0, 0.0));
        transform = glm::rotate(transform, eulerAngles[0], glm::vec3(1.0, 0.0, 0.0));
        transform = glm::rotate(transform, eulerAngles[2], glm::vec3(0.0, 0.0, 1.0));
        applyTransform(transformMode, transform);
    }

    void Mesh::applyTranslation(TransformMode transformMode, const glm::vec3 &translation)
    {
        glm::mat4 translationMatrix = glm::translate(translation);
        applyTransform(transformMode, translationMatrix);
    }

    void Mesh::applyScale(TransformMode transformMode, const glm::vec3 &scale)
    {
        glm::mat4 scaleMatrix = glm::scale(scale);
        applyTransform(transformMode, scaleMatrix);
    }

    void Mesh::setUniformColor(const glm::vec3 &color)
    {
        for (geometry::Vertex &vertex : _vertices)
        {
            vertex.color = color;
        }
    }

    void Mesh::createVertexBuffer(const renderer::vulkan::VulkanRenderer &renderer)
    {
        VkDeviceSize bufferSize = sizeof(getVertices()[0]) * getVertices().size();

        renderer::vulkan::BufferType stagingBuffer =
            renderer::vulkan::builders::StagingBufferBuilder(renderer)
                .withSize(bufferSize)
                .withData(getVertices().data())
                .build();

        _vertexBuffer =
            renderer::vulkan::builders::VertexBufferBuilder(renderer).withSize(bufferSize).build();

        stagingBuffer->copyInto(*_vertexBuffer);
    }

    void Mesh::createIndexBuffer(const renderer::vulkan::VulkanRenderer &renderer)
    {
        VkDeviceSize bufferSize = sizeof(getIndices()[0]) * getIndices().size();

        renderer::vulkan::BufferType stagingBuffer =
            renderer::vulkan::builders::StagingBufferBuilder(renderer)
                .withSize(bufferSize)
                .withData(getIndices().data())
                .build();
        _indexBuffer =
            renderer::vulkan::builders::IndexBufferBuilder(renderer).withSize(bufferSize).build();

        stagingBuffer->copyInto(*_indexBuffer);
    }

    void Mesh::createBuffers(const renderer::vulkan::VulkanRenderer &renderer)
    {
        createVertexBuffer(renderer);
        createIndexBuffer(renderer);
    }

    void Mesh::print(std::ostream &ostr) const
    {
        io::logging::Logger::trace(ostr,
                                   "Drawing " + std::to_string(getVertices().size())
                                       + " vertices and " + std::to_string(getIndices().size())
                                       + " segments (=" + std::to_string(getIndices().size() / 3)
                                       + " triangles)",
                                   { "DRAWING" });
    }

} // namespace brasio::mesh
