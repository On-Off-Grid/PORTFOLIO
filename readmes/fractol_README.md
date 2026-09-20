# 🌀 Fract'ol — Interactive 2D Fractal Renderer in C

> An interactive, real-time graphical fractal exploration application written in C using **MiniLibX** (X11 graphics library). Features smooth zooming, dynamic panning, customizable color palettes, and multiple fractal sets calculated via complex mathematics and escape-time algorithms.

---

## 💡 Overview

### For Non-Technical Recruiters
**Fract'ol** is a desktop application that renders infinite, self-similar mathematical patterns called **fractals** in real time. 
Instead of loading pre-rendered images, the application calculates every single pixel on the fly by processing complex mathematical equations hundreds of times per second. Users can navigate through these mathematical landscapes seamlessly—zooming in towards infinity, moving across the complex plane, and dynamically changing color schemes.

### For Technical Recruiters & Engineers
This project demonstrates proficiency in **low-level C programming**, **computer graphics**, **complex number mathematics**, **framebuffer manipulation**, and **event-driven interactive systems**. 
- Built from scratch in standard **C (C99)** following strict memory management and coding guidelines.
- Directly writes raw pixel bytes into image buffer memory using pointer arithmetic and bit-shifting before pushing frames to the X11 window display.
- Implements custom mathematical algorithms including coordinate mapping, floating-point string parsing (`ft_atof`), HSV-to-RGB color spectrum conversion, and escape-time calculations.

---

## 🎨 Supported Fractals

| Fractal | Description | Formula |
| :--- | :--- | :--- |
| **Mandelbrot Set** | The classic fractal set defined by iteration starting from zero for every complex point \(c\). | \(z_{n+1} = z_n^2 + c \quad (z_0 = 0)\) |
| **Julia Set** | Explores the Julia continuum by fixing constant \(c\) and varying initial starting point \(z_0\). Supports command-line parameters. | \(z_{n+1} = z_n^2 + c \quad (z_0 = x + iy)\) |
| **Burning Ship** | A variation of the Mandelbrot set applying absolute values to real and imaginary components before squaring, producing ship-like structures. | \(z_{n+1} = (\|\text{Re}(z_n)\| + i \|\text{Im}(z_n)\|)^2 + c\) |

---

## 🛠️ Technical Architecture & Key Concepts Learned

### 1. Complex Numbers & Escape-Time Algorithm
- **Complex Plane Mapping**: Translates pixel coordinates \((x, y)\) on an \(800 \times 800\) canvas to continuous complex coordinates \((a + bi) \in \mathbb{C}\).
- **Divergence Criteria**: Iterates until the magnitude squared exceeds the threshold (\(|z|^2 = \text{Re}(z)^2 + \text{Im}(z)^2 > 4.0\)) or reaches the maximum iteration depth (`MAX_ITER`).
- **Escape Ratio**: The number of iterations needed for a point to escape determines its pixel color. Points remaining within the bound after `MAX_ITER` are treated as part of the fractal set body (colored black).

### 2. Low-Level Framebuffer Optimization
- Rather than invoking slow drawing primitives per pixel, the renderer writes raw 32-bit ARGB values directly into a contiguous MiniLibX image buffer array (`char *addr`).
- Uses bitwise shifting for color construction: `(r << 16) | (g << 8) | b`.
- Pushes the complete framebuffer to the window display in a single `mlx_put_image_to_window` call per frame for optimal rendering speed.

### 3. Smooth Mouse-Centered Zoom & Panning
- **Cursor-Centric Zoom**: Adjusts the complex bounds \([x_{\text{min}}, x_{\text{max}}] \times [y_{\text{min}}, y_{\text{max}}]\) relative to the current mouse position, ensuring that the point under the cursor remains fixed during zooming.
- **Dynamic Panning**: Translates the window viewport across the complex plane in response to arrow key events.

### 4. Color Theory (HSV to RGB)
- Maps escape iteration counts to the **HSV (Hue, Saturation, Value)** color space.
- Dynamically converts HSV values into RGB tuples, allowing smooth continuous gradients and color cycling (`C` key) without hardcoding static color maps.

### 5. Memory Safety & Resource Management
- Ensures clean window destruction, display termination, and heap memory deallocation on application exit.
- Built without memory leaks (`valgrind` verified).

---

## 🗂️ Project Structure

```
fractol/
├── fractol.h                # Central header containing structures, macros, and function prototypes
├── fractol.c                # Entry point, initialization, command-line argument parsing, usage message
├── fractal_algorithms.c     # Mathematical calculations for Mandelbrot, Julia, and Burning Ship sets
├── event_handlers.c         # Interactive event hooks (keyboard navigation, mouse wheel zoom)
├── color_utils.c            # RGB bit manipulations, HSV-to-RGB conversion, and smooth palette generation
├── utils.c                  # Pixel buffer manipulation, complex number init, coordinate mapping
├── ft_atof.c                # Custom ASCII-to-float string parser for command-line Julia parameters
├── libft/                   # Custom C standard library helper functions
└── Makefile                 # Build automation script supporting all, clean, fclean, re
```

---

## 🚀 Getting Started

### Prerequisites
- Operating System: **Linux** (X11 environment) or **macOS**
- Compiler: `gcc` or `clang` with `make`
- Required Libraries: `libX11`, `libXext`, `libm`

### Building the Project
Clone the repository and compile using `make`:
```bash
git clone https://github.com/your-username/fractol.git
cd fractol
make
```

### Usage
Run the binary followed by the desired fractal set name:

```bash
# Launch Mandelbrot Set
./fractol mandelbrot

# Launch Julia Set with default parameters (-0.7 + 0.27015i)
./fractol julia

# Launch Julia Set with custom complex parameters (e.g., c = -0.4 + 0.6i)
./fractol julia -0.4 0.6

# Launch Burning Ship Fractal
./fractol burning_ship
```

---

## 🎮 Controls

| Input | Action |
| :--- | :--- |
| **Mouse Wheel Up / Down** | Zoom in / Zoom out (centered at cursor) |
| **Arrow Keys ($\leftarrow \rightarrow \uparrow \downarrow$)** | Pan view across complex plane |
| **C Key** | Cycle color palette / shift hue |
| **+ / - Keys** | Increase / Decrease max iteration detail |
| **ESC Key / Window Cross** | Exit application cleanly |

---

## 🎓 Skills Summary

- **Language**: C (C99, POSIX)
- **Computer Graphics**: Framebuffers, MiniLibX, X11 Events, Double Buffering concepts
- **Mathematics**: Complex numbers, Polynomial iterations, Non-linear dynamics, Coordinate transformations
- **Software Engineering**: Modular code structure, Event-driven architecture, Pointer arithmetic, Memory management

---
*Created as part of the 42 Network Curriculum.*
