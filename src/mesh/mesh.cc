#include <mesh/mesh.hh>

#include <glm/gtx/transform.hpp>

namespace brasio::mesh
{

    Mesh::Mesh(const std::vector<geometry::Vertex> &vertices)
        : _vertices(vertices)
    {}

    void Mesh::draw(const Renderer &renderer)
    {}
    void Mesh::drawWireframe(const Renderer &renderer)
    {}

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

} // namespace brasio::mesh
