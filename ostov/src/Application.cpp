#include <ostov/application.h>
#include <iostream>
#include <cstdio>

// Temporary imports to verify linking (will be moved to Window class later)
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Ostov {

    Application::Application() {
    }

    Application::~Application() {
    }

    void Application::Run() {
        std::printf("--------------------------------------------------\n");
        std::printf(" OSTOV Engine (Core) | Initializing...\n");
        std::printf("--------------------------------------------------\n");
        
        // Basic GLFW init just to prove we linked external vendors correctly
        if (!glfwInit()) {
            std::printf("[Ostov Error] Failed to init GLFW!\n");
            return;
        }

        // Create a dummy hidden window just to get a context (Temporary)
        // In the real version, Window::Create() will do this.
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        GLFWwindow* window = glfwCreateWindow(640, 480, "Ostov Context", NULL, NULL);
        if (!window) {
             std::printf("[Ostov Error] Failed to create window!\n");
             return;
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::printf("[Ostov Error] Failed to initialize GLAD!\n");
            return;
        }

        std::printf("[Ostov] OpenGL Info:\n");
        std::printf("  Vendor:   %s\n", glGetString(GL_VENDOR));
        std::printf("  Renderer: %s\n", glGetString(GL_RENDERER));
        std::printf("  Version:  %s\n", glGetString(GL_VERSION));
        std::printf("--------------------------------------------------\n");

        OnInit();

        while (m_Running && !glfwWindowShouldClose(window)) {
            glfwPollEvents();
            OnUpdate();
            glfwSwapBuffers(window);
        }
        
        OnShutdown();
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}
