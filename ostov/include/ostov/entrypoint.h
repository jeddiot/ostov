#pragma once

#ifdef OSTOV_PLATFORM_WINDOWS

extern Ostov::Application* Ostov::CreateApplication();

int main(int argc, char** argv) {
    auto app = Ostov::CreateApplication();
    app->Run();
    delete app;
}

#endif
