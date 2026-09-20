# 🎓 Academic Software Engineering & Systems Portfolio
### Two-Year Learning Progression & Technical Evaluation

Welcome to my two-year Software Engineering & Systems Programming portfolio. This repository brings together key projects, infrastructure implementations, and algorithmic systems developed over the past two years of study. 

It is structured as an **umbrella repository** leveraging **Git Submodules** to showcase both standalone software projects and integrated multi-repository architectures.

---

## 📌 Executive Summary for Evaluation

Over the past two years, my focus has spanned **systems-level C programming**, **object-oriented design in C++**, **computer graphics and algorithmic mathematics**, **network protocol implementation**, and **DevOps / web infrastructure orchestration**.

### Core Engineering Capabilities Demonstrated:
1. **Low-Level Systems & Kernel Concepts**: Manual memory management (Valgrind-clean), POSIX signal handling, process lifecycle management (`fork`, `execve`, `waitpid`), and anonymous pipe redirection.
2. **Concurrency & Multithreading**: Thread synchronization with POSIX threads (`pthread`), race condition elimination via mutexes, and deadlock prevention algorithms (Dining Philosophers).
3. **Network Programming & Protocol Engineering**: Non-blocking I/O multiplexing (`poll`/`select`), socket programming, and full RFC-compliant protocol parsing (IRC server).
4. **Object-Oriented Programming (C++)**: Advanced C++ concepts, template metaprogramming, STL data structures, canonical form compliance, and inheritance dynamics.
5. **Computer Graphics & Applied Math**: Real-time 3D raycasting graphics engines, vector mathematics, trigonometric projections, and complex number fractal calculations.
6. **DevOps & Infrastructure as Code**: Multi-container Docker deployment built entirely from minimal base OS images, reverse proxies (Nginx), TLS 1.3 encryption, and software-defined private networking.

---

## 📂 Portfolio Curriculum & Project Index

Below is an overview of the core projects contained in this repository, grouped by technical domain:

### 1. ⚙️ Systems Programming & Operating Systems (C)

| Project | Key Concepts & Technologies | Highlights |
| :--- | :--- | :--- |
| **[minishell](minishell/)** | POSIX C, Shell Architecture, Process Control, AST Parsing, Signals, Environment | A fully functional UNIX shell handling command parsing, pipelines (`\|`), file redirections (`<`, `>`, `>>`), Heredocs (`<<`), signal propagation (`SIGINT`, `SIGQUIT`), and built-ins. |
| **[philosophers](philosophers/)** | Concurrency, POSIX Threads (`pthread`), Mutex Locks, Synchronization | Deadlock-free, starvation-free simulation of Dijkstra's Dining Philosophers problem using memory-address-ordered lock acquisition. |
| **[minitalk](minitalk/)** | Inter-Process Communication (IPC), Bitwise Operations, UNIX Signals | A bit-level IPC application transmitting strings over OS signals (`SIGUSR1`/`SIGUSR2`) with a custom synchronous ACK handshake protocol. |

---

### 2. 🌐 Object-Oriented Programming & Network Engineering (C++)

| Project | Key Concepts & Technologies | Highlights |
| :--- | :--- | :--- |
| **[my_irc](my_irc/)** | C++98 / C++11, Sockets, Non-Blocking I/O (`poll`), IRC RFC 1459/2812 | A multi-client IRC server handling concurrent non-blocking socket connections, channel management, operator privileges, and command parsing. |
| **[CPPS](CPPS/)** | C++ OOP, Inheritance, Polymorphism, Templates, STL, Orthodox Canonical Form | Comprehensive C++ module suite covering memory management, abstract classes, templates, container adapters, and algorithm design. |

---

### 3. 🎨 Computer Graphics & Applied Mathematics

| Project | Key Concepts & Technologies | Highlights |
| :--- | :--- | :--- |
| **[cub3d](cub3d/)** | Raycasting, Linear Algebra, Trigonometric Projection, MiniLibX, X11 | A 3D graphical engine written in C using DDA raycasting algorithms to render textured environments, wall collisions, and dynamic camera movement. |
| **[fractol](fractol/)** | Complex Numbers, Fractal Geometry, Escape-Time Algorithms, Color Mapping | Real-time interactive fractal renderer for Mandelbrot and Julia sets with smooth HSV-to-RGB color spectrum mapping and zoom controls. |

---

### 4. 🐳 DevOps, Infrastructure & System Administration

| Project | Key Concepts & Technologies | Highlights |
| :--- | :--- | :--- |
| **[inception](inception/)** | Docker, Docker Compose, Nginx, MariaDB, WordPress, TLS 1.3, Virtual Networks | A zero-trust production web stack built from custom minimal `debian` base Dockerfiles. Enforces HTTPS entry, private backend networks, and persistent volume storage. |

---

### 5. 📚 Software Architecture & Documentation

| Resource / Directory | Description |
| :--- | :--- |
| **[readmes/](readmes/)** | Detailed technical documentations and executive summaries for each project. |
| **[git_workflow.md](git_workflow.md)** | Engineering guide covering feature-branch Git workflows and Pull Request standards. |
| **[ROADMAP_2026.md](ROADMAP_2026.md)** | Strategic learning roadmap and skill progression outline. |
| **[Patterns-in-code-and-culture](Patterns-in-code-and-culture/)** | Explorations into software design patterns, architectural principles, and engineering culture. |

---

## 🛠️ Repository Architecture & Build Verification

This workspace is organized using Git Submodules to ensure each major project retains its independent version history while providing a unified view for evaluation.

### How to Clone & Build

To evaluate this repository locally with all sub-projects intact:

```bash
# Clone the repository along with all nested submodules
git clone --recurse-submodules git@github.com:On-Off-Grid/PORTFOLIO.git
cd PORTFOLIO

# Alternatively, if cloned normally:
git submodule update --init --recursive
```

### Compiling Individual Projects
Each C and C++ project includes a dedicated `Makefile` adhering to strict compilation flags (`-Wall -Wextra -Werror`):

```bash
# Example: Building Minishell
cd minishell && make

# Example: Building Cub3D
cd ../cub3d && make

# Example: Running Inception Infrastructure
cd ../inception && docker compose up --build
```

---

## 📈 Summary of Learning Progression

- **Year 1**: Mastery of C fundamentals, pointers, dynamic memory management (`malloc`/`free`), algorithms, UNIX system calls, bitwise operations, and low-level graphics rendering.
- **Year 2**: Transition to Object-Oriented Programming (C++), multi-threaded concurrency, network socket programming, complex system architecture, and DevOps infrastructure automation.

Thank you for reviewing my work! Please feel free to inspect individual project directories or consult [readmes/](readmes/) for deep-dive architectural specifications.
