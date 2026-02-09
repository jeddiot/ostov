#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace Ostov {

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoord;
    };

    class Mesh {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
        ~Mesh();

        // OpenGL handles (will be managed internally)
        uint32_t GetVAO() const { return m_VAO; }
        uint32_t GetIndexCount() const { return static_cast<uint32_t>(m_Indices.size()); }

    private:
        void SetupMesh();

        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;
        uint32_t m_VAO = 0, m_VBO = 0, m_EBO = 0;
    };

}
