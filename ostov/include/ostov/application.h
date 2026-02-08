#pragma once
#include "core.h"

namespace Ostov {

    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        virtual void OnInit() {}
        virtual void OnUpdate() {}
        virtual void OnShutdown() {}
    
    private:
        bool m_Running = true;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}
