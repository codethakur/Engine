# Engine
> A C++ engine built from scratch with OpenGL — covering rendering, physics, UI, scene serialization, 2D/3D, and GLTF model loading. A small FPS is included as an integration test to validate all systems working together.

<img width="1431" height="827" alt="Engine" src="https://github.com/user-attachments/assets/55b2ba66-766a-4171-95c0-3e628afb2b25" />

---

## What is this?

This is not a tutorial follow-along. It's a hand-built C++ engine covering most of the systems a real engine needs:

- **Rendering** — OpenGL pipeline, lighting, materials, textures, GLTF model loading
- **Physics** — Bullet3 integration wrapped in a custom component layer (`RigidBody`, `BoxCollider`, `KinematicCharacterController`)
- **Entity-Component System** — scene graph, `GameObject`, reusable components, type registration
- **Scene serialization** — entire scenes defined in JSON `.sc` files, nothing hardcoded
- **UI system** — Canvas, TextComponent, ButtonComponent, Anchor/Pivot layout, mouse hit detection
- **2D support** — `SpriteComponent`, UV tiling, 2D transforms alongside 3D
- **Audio** — `AudioComponent` + `AudioListenerComponent` (3D positional audio architecture)
- **Animation** — `AnimationComponent` for animated objects
- **ImGui integration** — HUD, pause menu, settings window (brightness, background color, volume)
- **Game state machine** — `Playing → Paused → MainMenu` with cursor lock/unlock

Built and maintained solo. Every wrapper, system, and integration written by hand.

---

## Screenshots

<img width="1274" height="830" alt="3D Scene" src="https://github.com/user-attachments/assets/2f2851bb-6d7d-43b8-8e07-2ac5fdbf1dc4" />

<p><strong>Diffuse Lighting</strong></p>
<img width="1202" height="837" alt="Diffuse Lighting" src="https://github.com/user-attachments/assets/03fddc7a-83d0-4655-8a4b-e102b35d923b" />

<p><strong>Ambient, Materials, Direct Light</strong></p>
<img width="1274" height="830" alt="Ambient Materials Direct Light" src="https://github.com/user-attachments/assets/ad88acc3-cfb4-47e3-b621-fa637022b460" />

<p><strong>Physics — Jump Platform (Bullet3 + KinematicCharacterController)</strong></p>
<img width="1274" height="830" alt="Jump Platform" src="https://github.com/user-attachments/assets/1c7791e0-da5b-438f-8d47-7550cf4da937" />

<p><strong>2D + UI System</strong></p>
<img width="1274" height="830" alt="2D and UI" src="https://github.com/user-attachments/assets/0276ea29-55cf-46c2-adb7-487563328f22" />

<p><strong>ImGui HUD — HP + Ammo overlay</strong></p>
<img width="1274" height="830" alt="HUD" src="https://github.com/user-attachments/assets/e36e17ae-5b53-4627-9e32-d4815a69babe" />

<p><strong>Pause Menu + Settings Window</strong></p>
<img width="1274" height="830" alt="Pause Menu" src="https://github.com/user-attachments/assets/5bf76f66-dde4-4926-b471-6fe5fc98395e" />

---

## Tech Stack

| Layer | Technology |
|---|---|
| Language | C++17 |
| Build System | CMake |
| Graphics API | OpenGL (via GLAD) |
| Windowing / Input | GLFW |
| Physics | Bullet3 (wrapped in custom component layer) |
| Model Loading | GLTF via custom loader |
| Texture Loading | stb_image |
| Scene Config | nlohmann/json |
| UI Overlay | ImGui |
| Audio | AudioComponent + AudioListenerComponent (3D positional) |
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

### 5. Physics Integration — Bullet3 Wrapper Layer
Bullet3 operates on its own object types (`btRigidBody`, `btCollisionShape`). Connecting it to the ECS required a clean wrapper so game code never touches Bullet directly.

**Fix:** Applied Y-axis flip inside the orthographic projection matrix for all UI rendering passes.

**Fix:** `PhysicsManager` owns the Bullet world. `RigidBody` and `BoxCollider` wrap Bullet types. `PhysicsComponent` bridges them into the ECS. `KinematicCharacterController` wraps Bullet's character controller for player movement with step/slope handling.
---

## Design Patterns Used

| Pattern | Where |
|---|---|
| **Factory** | Component and scene object creation, type registry |
| **Facade** | Engine subsystem API (`eng::Engine::GetInstance()`) |
| **Composite** | UI Canvas → Component tree, GameObject hierarchy |
| **Observer / Delegate** | Input events, `onClick` button callbacks |
| **Wrapper / Adapter** | Physics layer over Bullet3 |

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
