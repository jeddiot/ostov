#include <ostov/RenderGraph.h>
#include <iostream>

namespace Ostov {

    RenderGraph::RenderGraph() {
    }

    RenderGraph::~RenderGraph() {
    }

    RenderPass& RenderGraph::AddPass(const std::string& name) {
        m_Passes.push_back({ name, nullptr });
        return m_Passes.back();
    }

    void RenderGraph::Execute() {
        // In a real render graph, this is where we would sort 
        // the passes based on dependencies/resources.
        
        for (auto& pass : m_Passes) {
            if (pass.Execute) {
                // std::cout << "[RenderGraph] Executing Pass: " << pass.Name << "\n";
                pass.Execute(m_Renderer);
            }
        }
    }

}
