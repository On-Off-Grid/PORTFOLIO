# Souhail's Systems & Security Roadmap

> This calendar tracks my progress across systems, networking, IoT, and security,
> with the blog **“Patterns in Code and Culture”** as a lightweight logbook.[memory:19][memory:20]

---

## Month 0 — Blog & Infra Base (Weeks 1–4)

### Objectives
- Host my existing HTML/CSS blog using the Inception Docker stack.[file:4][memory:16]
- Turn the blog into a simple “Now + logbook” space, not a big frontend project.
- Prepare ground for systems, IoT, and security work in Months 1–3.

### Week 1
- [ ] Review current blog repo structure (HTML/CSS, `index.html`, pillars, post templates).[memory:18]
- [ ] Clean obvious layout issues only (containers, alignment, typography basics).
- [ ] Add a simple `Now` page or section describing what I am currently working on.

### Week 2
- [ ] Extend Inception stack so Nginx serves the static blog as the main site.[file:4]
- [ ] Configure HTTPS via self-signed TLS certificates (TLS 1.2/1.3).
- [ ] Verify local access at `https://souhail.local` or similar hostname.

### Week 3
- [ ] Decide how to store posts: 
      - Option A: Use WordPress within Inception as backend for blog posts.
      - Option B: Keep posts as markdown/HTML files and let agent manage them.[file:4]
- [ ] Add categories for posts: `systems`, `networking`, `embedded-iot`, `security`, `meta`.

### Week 4
- [ ] Publish a short “Roadmap” post summarizing this file for myself.
- [ ] Set rule: Blog changes only via small agent-driven tasks, no long manual refactors.

---

## Month 1 — Systems & Networking Focus (Weeks 5–8)

### Objectives
- Polish ft_irc and minishell to internship-ready quality.[file:2][file:3]
- Build small reusable networking tools.
- Use the blog only to log milestones (short posts).

### Week 5
- [ ] Add logging and basic config file to `ft_irc` (ports, limits, log levels).[file:2]
- [ ] Write a short architecture note (event loop, non-blocking sockets) in the README.
- [ ] Blog: publish a short ft_irc overview post (max 800 words).

### Week 6
- [ ] Add tests for minishell: pipelines, heredoc, expansion, builtins.[file:3]
- [ ] Document design choices (lexer → parser → executor) and benchmarks.
- [ ] Blog: minishell internals post (focus on parsing and execution, short).

### Week 7
- [ ] Start NetToolkit: C/C++ small networking tools (echo server, HTTP client, port scanner).
- [ ] Use modern C++ locally (C++17) even if cursus was C++98.[file:8]
- [ ] Blog: short note “NetToolkit: generalizing IRC knowledge into tools.”

### Week 8
- [ ] Build Packet Playground using `libpcap` to inspect headers and flags.
- [ ] Capture a few example traces and note interesting patterns.
- [ ] Blog: micro‑post on packets and headers (just diagrams + bullet points).

---

## Month 2 — Embedded & Agricultural IoT (Weeks 9–12)

### Objectives
- Connect sensors (soil/temperature) to a gateway (ESP32/RPi) via MQTT.[memory:17]
- Build a minimal dashboard to visualize data and decisions.
- Use blog as lab notebook (short field notes, not polished essays).

### Week 9
- [ ] Set up hardware (ESP32/RPi, sensors, wiring).
- [ ] Implement basic firmware to read sensors and publish MQTT messages.

### Week 10
- [ ] Host MQTT broker (Mosquitto) either inside Inception or on a local machine.[file:4]
- [ ] Build small backend (Python/Node) to subscribe, store data (SQLite/files), expose REST.

### Week 11
- [ ] Implement simple irrigation controller logic (thresholds, schedules, toggling LED/relay).
- [ ] Add a basic HTML/JS dashboard for data and controller state.

### Week 12
- [ ] Blog: “Field notes” posts (hardware, protocol, failures).
- [ ] Document power considerations and failure modes (gateway down, broker down).

---

## Month 3 — Security & Bug Bounty Automation (Weeks 13–16)

### Objectives
- Build recon automation CLI for bug bounty workflows.[memory:17]
- Implement a simple protocol/web fuzzer for own test infrastructure.
- Use blog for public write‑ups and methodology notes.

### Week 13
- [ ] Design recon CLI: config file format, logs, output directories.
- [ ] Integrate existing tools (nmap, ffuf, nuclei) through orchestrated shell/Python.

### Week 14
- [ ] Add safety checks and clear target scope (only permitted domains/labs).
- [ ] Blog: post on recon automation, focusing on workflow and ethics.

### Week 15
- [ ] Implement simple HTTP/protocol fuzzer aimed at test services (ft_irc, local web app).[file:2][file:4]
- [ ] Collect crashes/timeouts and log anomalies.

### Week 16
- [ ] Write 1–2 technical write‑ups on lab findings and bugs.
- [ ] Blog: “Findings & write‑ups” section linking to those posts.

---

## Ongoing Habits

- Weekly:
  - [ ] Update `Now` section on blog with current focus.
  - [ ] Write at least one short note or log entry per week (even 5–10 lines).

- Monthly:
  - [ ] Review this roadmap and adjust if needed.
  - [ ] Export a summary (bullet list) of completed tasks for CV/GitHub.

- Principle:
  - Blog tweaks = agent-driven small tasks.
  - My time = learning and building systems, IoT, and security tools.

