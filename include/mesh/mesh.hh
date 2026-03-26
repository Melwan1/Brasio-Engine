#pragma once

#include <glm/glm.hpp>
#include <renderer/renderer.hh>

#include <geometry/vertex.hh>
#include <mesh/transform-mode.hh>

namespace brasio::mesh
{

    class Mesh
    {
    public:
        Mesh(const std::vector<geometry::Vertex> &vertices,
             const std::vector<uint16_t> &indices);

        const std::vector<geometry::Vertex> &getVertices() const;
        std::vector<geometry::Vertex> &getVertices();
        const std::vector<uint16_t> &getIndices() const;
        std::vector<uint16_t> &getIndices();

        void draw(const renderer::Renderer &renderer);
        void drawWireframe(const renderer::Renderer &renderer);

        void applyTransform(TransformMode transformMode,
                            const glm::mat4 &transform);

        void applyRotate(TransformMode transformMode,
                         const glm::vec3 &eulerAngles);

        void applyTranslation(TransformMode transformMode,
                              const glm::vec3 &translation);

        void applyScale(TransformMode transformMode, const glm::vec3 &scale);

    private:
        std::vector<geometry::Vertex> _vertices;
        std::vector<uint16_t> _indices;

        glm::mat4 _transformGPU;
        glm::mat4 _transformCPU;
    };

} // namespace brasio::mesh
