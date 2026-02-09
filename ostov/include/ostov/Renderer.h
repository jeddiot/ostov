#pragma once

#include "Mesh.h"
#include <glm/glm.hpp>

namespace Ostov {

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        // 这里就是解决你疑问的关键：
        // 渲染器不决定圆球长什么样，它只负责把用户准备好的 Mesh (顶点) 投影到屏幕上。
        void Submit(const Mesh& mesh);

        // 状态设置：集中管理 OpenGL 状态，防止乱码
        void SetClearColor(const glm::vec4& color);
        void Clear();

        void SetDepthTest(bool enabled);
        
    private:
        // 可以在这里做状态缓存 (State Caching)
    };

}
