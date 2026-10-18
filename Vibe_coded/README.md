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
| **Ult Harness** — control plane (v3.0.0) | [On-Off-Grid/Ult_harness](https://github.com/On-Off-Grid/Ult_harness) | Python · FastAPI · multi-agent orchestration | Specification-driven control plane over 8 integrated recon/exploit components: egress/scope compliance, 16 specialist agents, free-first 4-tier model routing (Groq/OpenRouter/Mistral/Gemini/Cloudflare + local Ollama/27B-GPU; GitHub Models retired upstream 2026-07-30), memory/RAG, and an operator war-room dashboard on `:8001`. **Status (Oct 2026):** S0–S5 (a+b) + S7 + **S8.1–S8.3** (Interactsh OOB correlation, reasoning-model empty-content guard, housekeeping sweep) of the v3 restart complete — control plane built, trust-audited, end-to-end integrated, **260-test suite green (1 warning, unrelated httpx2/Starlette)**; S5b (live per-provider verification) **PASSED** post top-up (5/6 providers live 200 + paid overflow resolved; GitHub Models reported unverified, upstream-retired); S8.2 additionally live-probed PASS at $0. **S8.4 build-complete:** one-command `main.py hunt` supervisor (preflight → Intigriti auto-fetch scope → init → $0 dry-run gate → boot → operator-selected `--tools` from a registry, all egress-gated through `:8080`) with honest pause/resume (`main.py resume` + `workspace/<p>/hunt_state.json` — durable reports/evidence/egress-log survive a stop; in-memory tasks/triage/budget/OOB session are stated as volatilized). Next: **the first live hunt** (target: DataCamp/Intigriti — verified runbook in `docs/examples/`, one-command path up top) + **S8.5** war-room visual smoke (during S8.4). Legacy v2.x doc corpus archived to `docs/archive/legacy-v2/` (index + supersession chain); hunt-day field manual at `docs/hunt_cheatsheet.md` (§3.0 one-command launch + pause/resume, scope intake incl. the Intigriti Researcher-API path via `scripts/fetch_intigriti_scope.py`, the manual browser path for API-less platforms (YesWeHack), manual live-run walkthrough as the fallback layer, pitfall table, $0 levers) + scope-file templates in `docs/scope_templates/` + a verified copy-paste worked example for one real program (DataCamp, Intigriti) in `docs/examples/datacamp_intigriti.md`. Entry points: `OPERATIONS.md` + `docs/hunt_cheatsheet.md` (start with the example for a concrete run) + `docs/hunt_workflow.md` (the mental model: how the 8 component repos fit together, the 3-channel component→harness contract, and the admiral's two orchestration modes — with the wired-vs-designed split stated plainly). |

> ⚠️ Authorized-testing note: the security tooling above is for use exclusively
> against targets you own or are explicitly authorized to test under a
> bug-bounty program's scope and rules.
