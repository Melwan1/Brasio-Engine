#include <mesh/sphere.hh>

namespace brasio::mesh
{

    Sphere::Sphere(unsigned nSlices, unsigned nStacks)
        : Mesh(Sphere::build(nSlices, nStacks))
    {}

    std::pair<std::vector<geometry::Vertex>, std::vector<uint16_t>>
    Sphere::build(unsigned nSlices, unsigned nStacks)
    {
        std::vector<geometry::Vertex> vertices;
        std::vector<uint16_t> indices;

        vertices.reserve(2 + (nStacks - 1) * nSlices); // wtf is this shit
        indices.reserve(3 * 2 * nSlices * nStacks);

        vertices.emplace_back(
            geometry::Vertex({ 0.0f, +0.5f, 0.0f }, { 0.5f, 0.5f, 0.5f }));
        vertices.emplace_back(
            geometry::Vertex({ 0.0f, -0.5f, 0.0f }, { 0.5f, 0.5f, 0.5f }));

        // vertices per stack and slice
        for (unsigned stack = 1; stack < nStacks; stack++)
        {
            float phi = std::numbers::pi * static_cast<float>(stack)
                / static_cast<float>(nStacks);

            for (unsigned slice = 0; slice < nSlices; slice++)
            {
                auto theta = 2 * std::numbers::pi * static_cast<float>(slice)
                    / static_cast<float>(nSlices);
                vertices.emplace_back(
                    geometry::Vertex({ 0.5f * std::sin(phi) * std::cos(theta),
                                       0.5f * std::cos(phi),
                                       0.5f * std::sin(phi) * std::sin(theta) },
                                     { 0.5f, 0.5f, 0.5f }));
            }
        }

        // indices

        // top and bottom triangles

        for (unsigned slice = 0; slice < nSlices; slice++)
        {
            indices.emplace_back((slice + 1) % nSlices + 2);
            indices.emplace_back(0);
            indices.emplace_back(slice + 2);

            indices.emplace_back(slice + (nStacks - 2) * nSlices + 2);
            indices.emplace_back(1);
            indices.emplace_back((slice + 1) % nSlices + (nStacks - 2) * nSlices
                                 + 2);
        }

        // triangles per stack / slice

        for (unsigned stack = 0; stack + 2 < nStacks; stack++)
        {
            unsigned firstOnStack = stack * nSlices + 2;
            unsigned firstOnNextStack = (stack + 1) * nSlices + 2;

            for (unsigned slice = 0; slice < nSlices; slice++)
            {
                indices.emplace_back(firstOnStack + slice);
                indices.emplace_back(firstOnNextStack + slice);
                indices.emplace_back(firstOnNextStack + (slice + 1) % nSlices);

                indices.emplace_back(firstOnNextStack + (slice + 1) % nSlices);
                indices.emplace_back(firstOnStack + (slice + 1) % nSlices);
                indices.emplace_back(firstOnStack + slice);
            }
        }

        return std::make_pair<>(vertices, indices);
    }

} // namespace brasio::mesh
