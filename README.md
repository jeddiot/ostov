# Ostov

## What is Ostov

Ostov is a production-grade, reusable render graph middleware for OpenGL 4.6+.

## Why Ostov

Most Game Engines are bloated with physics, audio, and ECS. Ostov is here to save the day. It is a specialized graphics abstraction layer that transforms spaghetti OpenGL calls into a structured, high-level render graph:

```cpp
auto& geometryPass = renderGraph.AddPass("Geometry");
geometryPass.SetOutput(gBuffer);
geometryPass.Execute = [&](Renderer& r) {
    r.DrawMesh(mesh, material);
};
```

## Key Features (Under development)

- **Render Graph Architecture:** Define complex frame pipelines (G-Buffer -> Shadow -> Lighting -> Bloom) as a dependency graph.
- **Direct State Access (DSA):** Built strictly on OpenGL 4.6 DSA for cleaner, safer, faster state management.
- **Hot-Reloading:** Shaders and Textures update instantly when files change on disk.
- **Asset Integration:** One-line mesh/texture loading (glTF, OBJ, PNG, HDR).
- **ImGui Built-in:** implicit debug inspectors for every internal object.

## Structure

- `ostov/`: The Static Library (Middleware).
- `examples/`: A client application demonstrating how to build a renderer on top of Ostov.

## Build and Run

```bash
cmake -S . -B build ; cmake --build build
# .\build\bin\examples_app.exe
```
