#include <mesh/mesh.hh>

#include <glm/gtx/transform.hpp>

#include <renderer/vulkan/builders/buffer-builder.hh>
#include <io/logging/logger.hh>

namespace brasio::mesh
{

    Mesh::Mesh(const std::vector<geometry::Vertex> &vertices,
               const std::vector<uint16_t> &indices)
        : _vertices(vertices)
        , _indices(indices)
    {}

    Mesh::Mesh(const std::pair<std::vector<geometry::Vertex>,
                               std::vector<uint16_t>> &vertices_indices)
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

    const std::vector<uint16_t> &Mesh::getIndices() const
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

    std::vector<uint16_t> &Mesh::getIndices()
    {
        return _indices;
    }

    void Mesh::draw(const VkCommandBuffer &commandBuffer,
                    const renderer::vulkan::VulkanRenderer &renderer) const
    {
        // print(std::cout);
        VkBuffer vertexBuffers[] = { getVertexBuffer()->getHandle() };
        VkDeviceSize offsets[] = { 0 };
        uint32_t firstBinding = 0;
        uint32_t bindingCount = 1;
        vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount,
                               vertexBuffers, offsets);
        vkCmdBindIndexBuffer(commandBuffer, getIndexBuffer()->getHandle(), 0,
                             VK_INDEX_TYPE_UINT16);
        vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                                renderer.getPipelineLayout().getHandle(), 0, 1,
                                &renderer.getDescriptorSets().getHandle().at(
                                    renderer.getCurrentFrame()),
                                0, nullptr);
        uint32_t instanceCount = 1;
        uint32_t firstVertex = 0;
        uint32_t firstInstance = 0;
        uint32_t instanceOffset = 0;
        vkCmdDrawIndexed(
            commandBuffer, static_cast<uint32_t>(getIndices().size()),
            instanceCount, firstVertex, firstInstance, instanceOffset);
    }
    void
    Mesh::drawWireframe(const VkCommandBuffer &commandBuffer,
                        const renderer::vulkan::VulkanRenderer &renderer) const
    {
        (void)commandBuffer;
        (void)renderer;
    }

    void Mesh::applyTransform(TransformMode transformMode,
                              const glm::mat4 &transform)
    {
        if (transformMode == TransformMode::CPU)
        {
            for (auto &vertex : _vertices)
            {
                vertex.position =
                    glm::vec3(transform * glm::vec4(vertex.position, 1.0));
            }
        }
        else
        {
            _transformGPU = transform * _transformGPU;
        }
    }

    void Mesh::applyRotate(TransformMode transformMode,
                           const glm::vec3 &eulerAngles)
    {
        glm::mat4 transform = glm::mat4(1.0);
        transform =
            glm::rotate(transform, eulerAngles[1], glm::vec3(0.0, 1.0, 0.0));
        transform =
            glm::rotate(transform, eulerAngles[0], glm::vec3(1.0, 0.0, 0.0));
        transform =
            glm::rotate(transform, eulerAngles[2], glm::vec3(0.0, 0.0, 1.0));
        applyTransform(transformMode, transform);
    }

    void Mesh::applyTranslation(TransformMode transformMode,
                                const glm::vec3 &translation)
    {
        glm::mat4 translationMatrix = glm::translate(translation);
        applyTransform(transformMode, translationMatrix);
    }

    void Mesh::applyScale(TransformMode transformMode, const glm::vec3 &scale)
    {
        glm::mat4 scaleMatrix = glm::scale(scale);
        applyTransform(transformMode, scaleMatrix);
    }

    void Mesh::createVertexBuffer(
        const renderer::vulkan::PhysicalDeviceType &physicalDevice,
        const renderer::vulkan::LogicalDeviceType &logicalDevice,
        const renderer::vulkan::CommandPoolType &commandPool)
    {
        VkDeviceSize bufferSize =
            sizeof(getVertices()[0]) * getVertices().size();

        VkBufferUsageFlags stagingBufferUsageFlags =
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        VkMemoryPropertyFlags stagingBufferMemoryFlags =
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
            | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

        renderer::vulkan::builders::BufferBuilder stagingBufferBuilder(
            physicalDevice, logicalDevice);
        stagingBufferBuilder.withSize(bufferSize)
            .withUsage(stagingBufferUsageFlags)
            .withData(getVertices().data())
            .withMemoryProperties(stagingBufferMemoryFlags);

        renderer::vulkan::BufferType stagingBuffer =
            stagingBufferBuilder.build();
        stagingBuffer->unmapMemory();

        VkBufferUsageFlags vertexBufferUsageFlags =
            VK_BUFFER_USAGE_TRANSFER_DST_BIT
            | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        VkMemoryPropertyFlags vertexBufferMemoryFlags =
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

        renderer::vulkan::builders::BufferBuilder vertexBufferBuilder(
            physicalDevice, logicalDevice);
        vertexBufferBuilder.withSize(bufferSize)
            .withUsage(vertexBufferUsageFlags)
            .withMemoryProperties(vertexBufferMemoryFlags);

        _vertexBuffer = vertexBufferBuilder.build();

        stagingBuffer->copyInto(*_vertexBuffer, commandPool->getHandle(),
                                bufferSize);
    }

    void Mesh::createIndexBuffer(
        const renderer::vulkan::PhysicalDeviceType &physicalDevice,
        const renderer::vulkan::LogicalDeviceType &logicalDevice,
        const renderer::vulkan::CommandPoolType &commandPool)
    {
        VkDeviceSize bufferSize = sizeof(getIndices()[0]) * getIndices().size();

        VkBufferUsageFlags stagingBufferUsageFlags =
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        VkMemoryPropertyFlags stagingBufferMemoryFlags =
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
            | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

        renderer::vulkan::builders::BufferBuilder stagingBufferBuilder(
            physicalDevice, logicalDevice);
        stagingBufferBuilder.withSize(bufferSize)
            .withUsage(stagingBufferUsageFlags)
            .withData(getIndices().data())
            .withMemoryProperties(stagingBufferMemoryFlags);

        renderer::vulkan::BufferType stagingBuffer =
            stagingBufferBuilder.build();
        stagingBuffer->unmapMemory();

        VkBufferUsageFlags indexBufferUsageFlags =
            VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        VkMemoryPropertyFlags indexBufferMemoryFlags =
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

        renderer::vulkan::builders::BufferBuilder indexBufferBuilder(
            physicalDevice, logicalDevice);
        indexBufferBuilder.withSize(bufferSize)
            .withUsage(indexBufferUsageFlags)
            .withMemoryProperties(indexBufferMemoryFlags);

        _indexBuffer = indexBufferBuilder.build();

        stagingBuffer->copyInto(*_indexBuffer, commandPool->getHandle(),
                                bufferSize);
    }

    void Mesh::createBuffers(
        const renderer::vulkan::PhysicalDeviceType &physicalDevice,
        const renderer::vulkan::LogicalDeviceType &logicalDevice,
        const renderer::vulkan::CommandPoolType &commandPool)
    {
        createVertexBuffer(physicalDevice, logicalDevice, commandPool);
        createIndexBuffer(physicalDevice, logicalDevice, commandPool);
    }

    void Mesh::print(std::ostream &ostr) const
    {
        std::ostringstream oss;
        oss << "Drawing " << getVertices().size() << " vertices and "
            << getIndices().size() << " segments (= " << getIndices().size() / 3
            << " triangles)\n";
        oss << "Indices: ";
        for (unsigned index = 0; index < getIndices().size(); index++)
        {
            oss << getIndices()[index] << " ";
        }
        io::logging::Logger::trace(ostr, oss.str(), { "DRAWING" });
    }

} // namespace brasio::mesh
