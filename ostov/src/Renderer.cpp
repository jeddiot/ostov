#include <ostov/Renderer.h>
#include <glad/glad.h>

namespace Ostov {

    Renderer::Renderer() {
    }

    Renderer::~Renderer() {
    }

    void Renderer::SetClearColor(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Renderer::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SetDepthTest(bool enabled) {
        if (enabled) glEnable(GL_DEPTH_TEST);
        else glDisable(GL_DEPTH_TEST);
    }

    void Renderer::Submit(const Mesh& mesh) {
        glBindVertexArray(mesh.GetVAO());
        glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, 0);
    }

}
