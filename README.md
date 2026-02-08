# ostov

**ostov** is a production-grade, reusable **Render Graph Middleware** for OpenGL 4.6+, geared towards Technical Artists and Engine Developers.

*"Ostov"* (Russian: Остов) means *Skeleton* or *Frame*—the indestructible hull that remains when the walls are stripped away.

## Philosophy

Most "Game Engines" are bloated with physics, audio, and ECS. **Ostov** is different. It is a specialized **Graphics Abstraction Layer**.

It transforms spaghetti OpenGL calls (`glBindBuffer`, `glVertexAttribPointer`) into a structured, high-level **Render Graph**:

```cpp
auto& geometryPass = renderGraph.AddPass("Geometry");
geometryPass.SetOutput(gBuffer);
geometryPass.Execute = [&](Renderer& r) {
    r.DrawMesh(mesh, material);
};
```

## Key Features (Planning)

- **Render Graph Architecture:** Define complex frame pipelines (G-Buffer -> Shadow -> Lighting -> Bloom) as a dependency graph.
- **Direct State Access (DSA):** Built strictly on OpenGL 4.6 DSA for cleaner, safer, faster state management.
- **Hot-Reloading:** Shaders and Textures update instantly when files change on disk.
- **Asset Integration:** One-line mesh/texture loading (glTF, OBJ, PNG, HDR).
- **ImGui Built-in:** implicit debug inspectors for every internal object.

## Structure

- **ostov/**: The Static Library (Middleware).
- **sandbox/**: A client application demonstrating how to build a renderer on top of Ostov.

## Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```
