#include <ostov/ostov.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

class ExampleApp : public Ostov::Application {
public:
    ExampleApp() {
        std::cout << "Example App Created!\n";
    }

    ~ExampleApp() {
    }

    void OnInit() override {
        std::cout << "ExampleApp::OnInit() - Generating Sphere...\n";

        // 1. 手动生成圆球顶点数据 (体现使用者的控制力)
        std::vector<Ostov::Vertex> vertices;
        std::vector<uint32_t> indices;
        
        const float radius = 0.8f;
        const int sectors = 36;
        const int stacks = 18;
        const float PI = 3.14159265359f;

        for (int i = 0; i <= stacks; ++i) {
            float stackAngle = PI / 2 - i * PI / stacks;
            float xy = radius * cosf(stackAngle);
            float z = radius * sinf(stackAngle);

            for (int j = 0; j <= sectors; ++j) {
                float sectorAngle = j * 2 * PI / sectors;
                float x = xy * cosf(sectorAngle);
                float y = xy * sinf(sectorAngle);

                Ostov::Vertex v;
                v.Position = { x, y, z };
                v.Normal = glm::normalize(v.Position);
                v.TexCoord = { (float)j / sectors, (float)i / stacks };
                vertices.push_back(v);
            }
        }

        for (int i = 0; i < stacks; ++i) {
            int k1 = i * (sectors + 1);
            int k2 = k1 + sectors + 1;
            for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
                if (i != 0) {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }
                if (i != (stacks - 1)) {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }
        }

        m_SphereMesh = std::make_unique<Ostov::Mesh>(vertices, indices);

        // 2. 创建一个简单的 Shader (显示法线颜色)
        std::string vShader = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aNormal;
            uniform mat4 u_ViewProj;
            out vec3 vNormal;
            void main() {
                vNormal = aNormal;
                gl_Position = u_ViewProj * vec4(aPos, 1.0);
            }
        )";

        std::string fShader = R"(
            #version 330 core
            in vec3 vNormal;
            out vec4 FragColor;
            void main() {
                // 将法线 [-1, 1] 映射到 [0, 1] 显示颜色
                FragColor = vec4(vNormal * 0.5 + 0.5, 1.0);
            }
        )";

        m_Shader = std::make_unique<Ostov::Shader>(vShader, fShader);

        // 3. 配置 RenderGraph
        auto& geometryPass = m_RenderGraph.AddPass("Geometry");
        geometryPass.Execute = [&](Ostov::Renderer& r) {
            r.SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            r.Clear();
            r.SetDepthTest(true);

            m_Shader->Bind();
            
            // 简单的旋转投影矩阵
            float time = (float)glfwGetTime();
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));
            glm::mat4 proj = glm::perspective(glm::radians(45.0f), 640.0f/480.0f, 0.1f, 100.0f);
            glm::mat4 model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0, 1, 0));
            
            m_Shader->SetUniformMat4("u_ViewProj", proj * view * model);
            
            r.Submit(*m_SphereMesh);
        };
    }

    void OnUpdate() override {
        m_RenderGraph.Execute();
    }

private:
    Ostov::RenderGraph m_RenderGraph;
    std::unique_ptr<Ostov::Mesh> m_SphereMesh;
    std::unique_ptr<Ostov::Shader> m_Shader;
};

Ostov::Application* Ostov::CreateApplication() {
    return new ExampleApp();
}
