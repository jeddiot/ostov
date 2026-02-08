#pragma once

#include "core.h"
#include <string>
#include <vector>
#include <functional>
#include <map>

namespace Ostov {

    // Simple placeholder for Renderer
    class Renderer {
    public:
        void DrawMesh() { /* TODO */ }
    };

    struct RenderPass {
        std::string Name;
        std::function<void(Renderer&)> Execute;

        // Future: Inputs and Outputs for dependency graph
        // void SetOutput(ResourceHandle resource);
    };

    class RenderGraph {
    public:
        RenderGraph();
        ~RenderGraph();

        RenderPass& AddPass(const std::string& name);
        void Execute();

    private:
        std::vector<RenderPass> m_Passes;
        Renderer m_Renderer; // The execution context
    };

}
