# cub3D - 2.5D Raycasting Game Engine

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Graphics](https://img.shields.io/badge/Graphics-MiniLibX%2F%20X11-orange.svg)
![Build](https://img.shields.io/badge/Build-Makefile-green.svg)
![License](https://img.shields.io/badge/License-42%20Network-lightgrey.svg)

> A custom-built, real-time **2.5D Raycasting graphics engine** written in **C** from scratch, inspired by the legendary 1992 FPS **Wolfenstein 3D**.

---

## 📌 Executive Summary

**cub3D** is a computer graphics project designed to explore low-level software rendering, vector mathematics, and graphics pipeline optimization without using modern 3D graphics APIs like OpenGL or DirectX. 

Starting from a blank C file and a minimal windowing library (MiniLibX), this project builds a complete software-rendered 3D environment out of a 2D map grid. It parses scene descriptions, casts rays in real-time, calculates wall distances, samples textures with sub-pixel precision, handles user input asynchronously, and enforces strict memory safety.

---

## 🎯 What Recruiters Should Know

| For Non-Technical Recruiters | For Technical Recruiters & Engineers |
| :--- | :--- |
| 🎮 **Functional 3D Game**: Interactive 3D maze environment with smooth movement, directional texture rendering, and custom color ceilings/floors. | 📐 **Math & Geometry**: Real-time DDA (Digital Differential Analysis) raycasting, vector projections, matrix rotations, and fisheye correction. |
| ⚡ **Built From Scratch**: Developed in pure C without 3D game engines (Unity/Unreal) or 3D libraries (OpenGL/DirectX). | 🚀 **Optimized Graphics**: Direct memory buffer manipulation (software frame buffering) to achieve 60+ FPS rendering without redraw lag. |
| 🛡️ **Robust Engineering**: Includes strict map validation, complete error handling, zero memory leaks, and standard OS signal handling. | 🏛️ **Clean Architecture**: Modular software architecture isolating parsing, graphics state, input hooks, raycasting logic, and cleanup handlers. |

---

## ✨ Key Features & Capabilities

- **Real-Time 2.5D Raycasting**: Converts 2D grid configurations into a full 3D perspective using line-by-line ray projection.
- **Directional Texture Mapping**: Identifies North, South, East, and West wall collisions to map four distinct XPM textures with correct UV alignment.
- **Continuous Kinematics & Physics**: Smooth multi-key player movement (WASD), camera rotation (Arrow keys), and wall collision detection with slide buffering.
- **Custom Config File Parser (`.cub`)**: Validates texture file paths, RGB color codes (0–255), grid layout integrity, and single player starting position/orientation.
- **Flood-Fill Map Boundary Validator**: Algorithmic validation using a flood-fill approach to ensure maps are completely enclosed by walls before launching the game loop.
- **Direct Frame Buffering**: Renders pixels directly into an off-screen memory array (`mlx_get_data_addr`) before pushing the completed frame to the window display.

---

## 🧠 Core Engineering & Mathematical Concepts

### 1. Raycasting & Digital Differential Analysis (DDA)
Instead of processing full 3D geometry with polygons, raycasting sends out a ray for each vertical column of the screen ($1280$ resolution = $1280$ rays).

- **Camera Space Mapping**: Maps screen column $x$ to camera coordinate $x \in [-1, 1]$.
$$\text{camera\_x} = \frac{2 \cdot x}{\text{WINDOW\_WIDTH}} - 1$$
- **DDA Grid Traversal**: Advances rays step-by-step through the 2D grid map until hitting a wall tile (`1`), executing in $O(N + M)$ time relative to map dimensions.
- **Fisheye Distortion Correction**: Uses perpendicular wall distance rather than Euclidean distance to prevent wall distortion near the screen edges:
$$\text{perp\_wall\_dist} = \frac{\text{map\_x} - \text{pos\_x} + \frac{1 - \text{step\_x}}{2}}{\text{ray\_dir\_x}}$$

```
Player (x, y) ──── Ray Direction ───► [ Wall Hit (1) ]
     │                                    │
     └── Perpendicular Distance Calculated ┘ ──► Vertical Slice Height
```

### 2. Camera Plane & Vector Rotations
The player camera uses a direction vector $\vec{D} = (dir\_x, dir\_y)$ and a perpendicular camera plane vector $\vec{P} = (plane\_x, plane\_y)$ defining a $66^\circ$ Field of View (FOV). Rotation uses 2D rotation matrix transformations:

$$\begin{pmatrix} dir\_x' \\ dir\_y' \end{pmatrix} = \begin{pmatrix} \cos(\theta) & -\sin(\theta) \\ \sin(\theta) & \cos(\theta) \end{pmatrix} \begin{pmatrix} dir\_x \\ dir\_y \end{pmatrix}$$

### 3. Software Frame Buffering & UV Texture Mapping
To prevent visual tearing and flickering, cub3D implements a software double-buffering pipeline:
1. Calculates `wall_x` (exact fractional hit location on the wall).
2. Maps `wall_x` to the texture column $x$-coordinate ($0 \rightarrow 63$).
3. Calculates vertical step size per screen pixel and samples texture color directly from raw memory pointers.
4. Writes RGB values to an off-screen pixel buffer (`t_image.addr`) before a single `mlx_put_image_to_window` call per frame.

---

## 🛠️ Tech Stack & Skills Demonstrated

- **Primary Language**: C (GCC 14 / C99 standard compliant with `-Wall -Wextra -Werror`).
- **Graphics & Windowing**: MiniLibX (X11 graphics wrapper for Linux).
- **Computer Science Concepts**:
  - Linear Algebra & Trigonometric Vector Projections
  - Software Rendering & Texture Interpolation
  - Graph Traversal & Flood-Fill Algorithms
  - Dynamic Memory Allocations (`malloc`, `free`, defensive pointer management)
  - Event-Driven Architecture (Key hooks, loop hooks, window destruction signals)
  - File I/O & Custom String Parsing (`Get Next Line`)

---

## 📂 Project Structure

```text
cub3d/
├── Makefile                # Build automation (all, clean, fclean, re)
├── includes/
│   ├── cub3d.h             # Master header with function prototypes & includes
│   └── structures.h        # Data structures (t_game, t_player, t_ray, t_map, etc.)
├── src/
│   ├── main.c              # Application entry point & game initialization
│   ├── init_game.c         # Memory allocation & default struct setup
│   ├── event_hooks.c       # X11 event hook binding (key press/release, close window)
│   ├── game_management.c   # Main game loop execution
│   ├── movement.c          # Player movement, rotation & collision physics
│   ├── raycast.c           # Ray initialization, DDA algorithm & wall distance
│   ├── raycast_utils.c     # Raycasting helper calculations
│   ├── render.c            # Slice projection & frame buffer rendering
│   ├── textures.c          # XPM texture loading & sub-pixel sampling
│   ├── parse_map.c         # Map structure validation & flood-fill verification
│   ├── parse_textures.c    # Texture path parsing & loading validation
│   ├── parse_colors.c      # Floor/ceiling RGB color parsing
│   ├── cleanup.c           # Memory cleanup & leak-free program termination
│   └── gnl.c               # Line-by-line configuration file reader
├── maps/                   # Test configuration files (.cub)
│   ├── maze.cub
│   ├── labyrinth.cub
│   └── chambers.cub
└── textures/               # Wall textures (.xpm)
    ├── north.xpm
    ├── south.xpm
    ├── east.xpm
    └── west.xpm
```

---

## 🚀 Installation & Running

### Prerequisites (Linux / Ubuntu)

Ensure standard build tools and X11 development libraries are installed:

```bash
sudo apt-get update
sudo apt-get install build-essential libx11-dev libxext-dev libbsd-dev
```

### Build Instructions

1. Clone the repository and navigate to the project directory:
   ```bash
   cd cub3d
   ```

2. Compile the project using the provided `Makefile`:
   ```bash
   make
   ```

3. Launch `cub3D` with a map configuration file:
   ```bash
   ./cub3D maps/maze.cub
   ```

---

## 🎮 Game Controls

| Action | Key / Input |
| :--- | :--- |
| **Move Forward / Backward** | <kbd>W</kbd> / <kbd>S</kbd> |
| **Strafe Left / Right** | <kbd>A</kbd> / <kbd>D</kbd> |
| **Rotate Camera** | <kbd>◄</kbd> / <kbd>►</kbd> (Left / Right Arrow) |
| **Exit Game** | <kbd>ESC</kbd> or Window <kbd>X</kbd> Button |

---

## 💡 Key Lessons & Takeaways

1. **Low-Level Math Applied to Graphics**: Translating theoretical trigonometry and linear algebra into fast, real-time code running at interactive frame rates.
2. **Defensive C Programming**: Handling edge cases in file parsing, validating array bounds, preventing memory leaks on error paths, and managing pointers safely.
3. **Optimizing Bottlenecks**: Learning how small inefficiencies inside loop bodies (like rendering loops executed $1280 \times 720$ times per frame) can impact CPU performance and how direct memory manipulation resolves bottlenecks.

---

<p align="center">
  <i>Developed by <b>souichou</b> as part of the 42 Network Curriculum.</i>
</p>
