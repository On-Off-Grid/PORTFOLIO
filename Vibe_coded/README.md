# 🤖 Vibe Coded — AI-Assisted Projects

Projects in this folder were built **with AI code generation in the loop**.
The architecture, specifications, security review and every merge decision are
mine; the implementation was produced and iterated with LLM agents. They are
kept separate from [`From_scratch/`](../From_scratch/) — where every line was
hand-written — so the distinction between the two working styles is honest and
visible.

Each directory below is a **standalone git repository** with its own remote,
history and license. They are intentionally *not* tracked by this umbrella
(which ignores everything in this folder except this README) — clone them
directly from the links:

| Project | Repository | Built with | Notes |
| :--- | :--- | :--- | :--- |
| **IgranSense MVP** | [On-Off-Grid/IgranSense_MVP](https://github.com/On-Off-Grid/IgranSense_MVP) | FastAPI · React/Vite · REST · Vercel | Full-stack product MVP: backend API, frontend, docs and deployment. |
| **pi-hunt** — bug-bounty harness | [On-Off-Grid/harness](https://github.com/On-Off-Grid/harness) | pi agent · MCP servers · RAG · recon pipelines | Autonomous hunting harness: coordinator + 25 specialist sub-agents, local evidence trails, installer + systemd units. |
| **Ult Harness** — control plane (v3.0.0) | [On-Off-Grid/Ult_harness](https://github.com/On-Off-Grid/Ult_harness) | Python · FastAPI · multi-agent orchestration | Specification-driven control plane over 8 integrated recon/exploit components: egress/scope compliance, 16 specialist agents, free-first model routing (Groq/OpenRouter/GitHub-Models/Mistral/Gemini + local Ollama), memory/RAG. **Status (Oct 2026):** S0–S4 of the v3 restart complete — control plane built, trust-audited, end-to-end integrated, **154-test suite green**; S5 (multi-provider router redesign) in progress. Entry point: `OPERATIONS.md`. |

> ⚠️ Authorized-testing note: the security tooling above is for use exclusively
> against targets you own or are explicitly authorized to test under a
> bug-bounty program's scope and rules.
