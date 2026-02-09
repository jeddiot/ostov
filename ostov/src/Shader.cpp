#include <ostov/Shader.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

namespace Ostov {

    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
            glDeleteShader(vertexShader);
            std::cout << "Vertex Shader Compilation Failed:\n" << &infoLog[0] << std::endl;
            return;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        source = fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);
            std::cout << "Fragment Shader Compilation Failed:\n" << &infoLog[0] << std::endl;
            return;
        }

        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);
        glLinkProgram(m_RendererID);

        GLint isLinked = 0;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);
            glDeleteProgram(m_RendererID);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            std::cout << "Shader Link Failed:\n" << &infoLog[0] << std::endl;
            return;
        }

        glDetachShader(m_RendererID, vertexShader);
        glDetachShader(m_RendererID, fragmentShader);
    }

    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }

    void Shader::Bind() const {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const {
        glUseProgram(0);
    }

    void Shader::SetUniformFloat4(const std::string& name, const glm::vec4& value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void Shader::SetUniformMat4(const std::string& name, const glm::mat4& value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

}
