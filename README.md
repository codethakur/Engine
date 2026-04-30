# Engine
> A custom 3D game engine built from scratch in C++ with OpenGL — including a fully playable first-person shooter built on top of it.

<img width="1431" height="827" alt="Engine" src="https://github.com/user-attachments/assets/55b2ba66-766a-4171-95c0-3e628afb2b25" />

---

## What is this?

This is not a tutorial follow-along. This is a hand-built 3D game engine written in C++, with its own:

- Rendering pipeline (OpenGL + GLAD + GLFW)
- Entity-component system
- Scene loader (JSON-based `.sc` files)
- Custom UI system with Canvas, TextComponent, and Button architecture
- Anchor/Pivot layout system
- Mouse hit detection in screen space
- A complete first-person shooter game built on top of the engine to stress-test every system

Built and maintained solo over several months. Every system designed, debugged, and iterated by hand.

---

## Screenshots

<img width="1274" height="830" alt="3D Scene" src="https://github.com/user-attachments/assets/2f2851bb-6d7d-43b8-8e07-2ac5fdbf1dc4" />

<p><strong>Diffuse Lighting</strong></p>
<img width="1202" height="837" alt="Diffuse Lighting" src="https://github.com/user-attachments/assets/03fddc7a-83d0-4655-8a4b-e102b35d923b" />

<p><strong>Ambient, Materials, Direct Light</strong></p>
<img width="1274" height="830" alt="Ambient Materials Direct Light" src="https://github.com/user-attachments/assets/ad88acc3-cfb4-47e3-b621-fa637022b460" />

<p><strong>Jump Platform</strong></p>
<img width="1274" height="830" alt="Jump Platform" src="https://github.com/user-attachments/assets/1c7791e0-da5b-438f-8d47-7550cf4da937" />

<p><strong>2D + UI System</strong></p>
<img width="1274" height="830" alt="2D and UI" src="https://github.com/user-attachments/assets/0276ea29-55cf-46c2-adb7-487563328f22" />

<p><strong>ImGui Integration — HUD (HP + Ammo)</strong></p>
<img width="1274" height="830" alt="HUD" src="https://github.com/user-attachments/assets/e36e17ae-5b53-4627-9e32-d4815a69babe" />

<p><strong>Pause Menu</strong></p>
<img width="1274" height="830" alt="Pause Menu" src="https://github.com/user-attachments/assets/5bf76f66-dde4-4926-b471-6fe5fc98395e" />

---

## Tech Stack

| Layer | Technology |
|---|---|
| Language | C++17 |
| Build System | CMake |
| Graphics API | OpenGL (via GLAD) |
| Windowing / Input | GLFW |
| Texture Loading | stb_image |
| Scene Config | nlohmann/json |
| UI Overlay | ImGui |
| Math | GLM |

---

## Engine Architecture

```
Engine
├── Core
│   ├── Game loop (fixed timestep)
│   ├── Scene management
│   └── JSON scene loader (.sc files)
├── Renderer
│   ├── OpenGL abstraction (VAO, VBO, shaders)
│   ├── Texture system (stb_image)
│   ├── Orthographic + Perspective projection
│   └── Lighting pipeline
├── Entity-Component System
│   ├── Component base class
│   ├── TransformComponent
│   ├── MeshRendererComponent
│   └── Custom game components (PlayerController, etc.)
├── UI System
│   ├── Canvas (root UI container)
│   ├── TextComponent
│   ├── ButtonComponent (with mouse hit detection)
│   └── Anchor/Pivot layout system
└── Input
    ├── GLFW input polling
    └── ImGui input isolation (WantCaptureMouse)
```

---

## Key Engineering Problems Solved

### 1. Mac Retina Display — Framebuffer vs Window Point Mismatch
On Mac with Retina (2x scaling), GLFW reports window coordinates in points while OpenGL framebuffer operates in pixels. Mouse hit detection was broken on all Retina displays because the coordinate spaces didn't match.

**Fix:** Query framebuffer size separately from window size and apply the correct scale factor before any hit-testing math.

### 2. ImGui + Game Input Isolation
Without isolation, clicking a UI button would simultaneously fire a bullet in the game world — ImGui and the engine were both consuming the same mouse event.

**Fix:** Check `ImGui::GetIO().WantCaptureMouse` at the top of the game update loop. If ImGui owns the input, clear all engine mouse state before PlayerController runs.

```
Frame starts
    ↓
GLFW collects all input events
    ↓
ImGui reads events → sets WantCaptureMouse = true
    ↓
Game::Update() checks WantCaptureMouse
    ↓
If true → clear all engine mouse states
    ↓
PlayerController runs → no mouse data → no camera move, no bullet fire
    ↓
ImGui renders its UI → button clicks work correctly
```

### 3. OpenGL Include Order (GLAD before GLFW)
GLFW conditionally includes system OpenGL headers. If GLFW is included before GLAD, GLAD's function pointer setup is overwritten. Caused silent failures that were hard to trace.

**Fix:** Enforced `glad.h` inclusion order before any GLFW header via a dedicated `gl_includes.h` umbrella header.

### 4. Orthographic Projection Y-Flip for UI
OpenGL's NDC has Y increasing upward. Screen space (where UI is designed) has Y increasing downward. Button positions were mirrored vertically.

**Fix:** Applied Y-axis flip inside the orthographic projection matrix for all UI rendering passes.

---

## Design Patterns Used

| Pattern | Where |
|---|---|
| **Factory** | Component and scene object creation |
| **Facade** | Engine subsystem API surface |
| **Composite** | UI Canvas → Component tree |
| **Observer / Delegate** | Input events, button callbacks |

---

## The Game Built On Top

A first-person shooter used to validate every engine system end-to-end:

- **First-person camera** with mouse look
- **Weapon system** with ammo tracking
- **HUD** (HP + Ammo) rendered via the engine's UI system
- **Main menu** (Play / Quit)
- **Pause menu** (Resume / Main Menu / Quit) with correct game state transitions
- **Scene loading** from JSON — entire level defined in a `.sc` file, no hardcoded positions

---

## Build Instructions

```bash
git clone https://github.com/codethakur/Engine.git
cd Engine
mkdir build && cd build
cmake ..
make
./out/Game
```

**Dependencies** (handled via CMake or bundled):
- OpenGL 3.3+
- GLFW 3.x
- GLAD (bundled)
- stb_image (bundled)
- nlohmann/json (bundled)
- ImGui (bundled)

---

## Status

Actively developed. Core engine systems are stable. Currently using it to build and test new game mechanics.

---

*Built by [Thakur](https://github.com/codethakur) · [LinkedIn](https://linkedin.com/in/thakurkishan)*
