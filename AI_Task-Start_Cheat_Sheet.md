# Souhail’s AI Task-Start Cheat Sheet
## Purpose
Use this before opening OpenCode or assigning work to an agent. The operating pattern is **human manager → bounded specialist task → verified artifact**, not “give a powerful model the repository and hope.” This matches the existing specification-driven, multi-agent approach used across the portfolio, blog and bug-bounty harness work.[^1][^2][^3]

The goal is to preserve three things:

- **Understanding:** the agent should accelerate learning, not replace it.
- **Ownership:** architecture, constraints, acceptance criteria and final approval remain human decisions.
- **Traceability:** every significant change should have a plan, diff, test result and attribution.
## Sixty-second router
| Task | Primary model | Fallback | Use it for |
|---|---|---|---|
| Current web research | **Deep Research Preview (Apr-21-2026)** | **Gemini 3.8 Flash** | Current APIs, libraries, CVEs, market/provider comparisons |
| Architecture or technical specification | **Nemotron 3 Ultra Free** | **Kimi K3-256K** | Boundaries, interfaces, schemas, trade-offs and phased plans |
| Large-repository analysis | **Kimi K3-256K** | **LongCat 2.5 Preview Free** | Mapping files, dependencies, control flow and implementation gaps |
| Multi-file implementation | **Ling 3.1 Flash Free** | **LongCat 2.5 Preview Free** | Planned changes across code, tests and documentation |
| Difficult implementation | **Kimi For Coding HighSpeed** | **DeepSeek V4.1 Flash** when AMD quota is available | Complex features and coordinated edits |
| Small code change | **GPT OSS 20B** on Groq | **Ling 3.0 Flash Fin Free** | One bug, one function, one CSS component or one test |
| Debugging from logs | **GPT OSS 120B** on Groq | **Gemini 3.8 Flash** | Root-cause analysis, minimal patch and regression test |
| Independent code review | **GPT OSS 120B** on Groq | **Nemotron 3 Ultra Free** | Diff review, edge cases, maintainability and missed requirements |
| C/C++ learning | **Gemini 3.8 Flash** | **GPT OSS 120B** | Explanations, exercises, UB analysis and modern equivalents |
| Security design review | **DeepSeek V4.1 Flash** when AMD quota is available | **Nemotron 3 Ultra Free** | Threat models, trust boundaries and defensive controls |
| Local/private security check | **Foundation-Sec-8B-Instruct Q4_K_M** through Ollama | None; escalate to a hosted reviewer after redaction | Secrets, unsafe scripts, unexpected egress and prompt injection |
| Authorized bug-bounty planning | **Nemotron 3 Ultra Free** | **DeepSeek V4.1 Flash** when available | Scope-aware test plans, evidence requirements and stop conditions |
| Blog outline and synthesis | **Gemini 3.8 Flash** | **Gemini Flash Latest** | Search intent, outline, evidence map and counterarguments |
| Blog prose editing | **Gemini Flash Latest** | **Ling 3.1 Flash Free** | Clarity, voice, structure and removal of generic AI phrasing |
| README/documentation | **Gemini 3.8 Flash** | **GPT OSS 20B** | Setup, architecture, limitations and reproducible examples |
| Prompt/specification refinement | **Nemotron 3 Ultra Free** | **Gemini 3.8 Flash** | Turning scattered requirements into executable instructions |
| RAG embeddings | **Gemini Embedding 2** | **Gemini Embedding 001** | Indexing notes, reports and repository documentation |
| Image generation/editing | **Nano Banana 2** | **Nano Banana 2 Lite** | Portfolio/blog visuals—not code or factual research |

**Default if uncertain:** use **Nemotron 3 Ultra Free** to clarify the task, then **Ling 3.1 Flash Free** to implement it, and **GPT OSS 120B** to review the diff. OpenCode labels its Zen free models as limited-time offers, so keep provider fallbacks ready.[^4]
## Preflight gate
Do not prompt an agent until every line has an answer.

```text
[ ] OUTCOME: What exact artifact must exist when this is done?
[ ] SCOPE: Which files, components, endpoints or sections may change?
[ ] NON-GOALS: What must not be redesigned or expanded?
[ ] SOURCE OF TRUTH: Which files/specifications/docs override everything else?
[ ] OWNERSHIP: What decisions must the agent ask me about?
[ ] RISK: Can this touch credentials, production, live targets or user data?
[ ] VALIDATION: Which commands/tests prove completion?
[ ] ACCEPTANCE: What observable conditions define “done”?
[ ] BUDGET: Is this worth a large model, or can a fast model handle it?
[ ] CHECKPOINT: Is the current work committed or backed up?
```

If three or more answers are unclear, do **not** begin implementation. Use **Nemotron 3 Ultra Free** to convert the idea into a one-page specification first.
## Complexity test
### Use one small model
Choose **GPT OSS 20B** when all are true:

- One or two files.
- The expected patch is small.
- Requirements are unambiguous.
- Existing tests expose success or failure.
- No architectural decision is required.
### Use planner, implementer, reviewer
Choose the full three-stage workflow when any are true:

- More than three files are involved.
- The task changes architecture, schemas or public interfaces.
- The repository is unfamiliar.
- Security, networking, concurrency or destructive operations are involved.
- The prompt contains several pages of requirements.
- A wrong answer can waste a day or corrupt working code.
### Use local-only first
Start with **Foundation-Sec-8B-Instruct Q4_K_M** through Ollama when material includes secrets, private targets, unpublished vulnerability evidence or sensitive logs. Ollama’s local API does not require authentication; local inference avoids hosted API quotas but remains limited by hardware and model capability.[^5][^6]
## Standard workflow
### Frame
**Model:** Nemotron 3 Ultra Free  
**Output:** `TASK_SPEC.md` or a concise plan in chat.

Ask it to produce:

- Objective and non-goals.
- Current-state findings tied to real files.
- Proposed changes by file.
- Risks and assumptions.
- Acceptance criteria.
- Test commands.
- Questions that genuinely block implementation.

Do not let the planner edit code.
### Map
**Model:** Kimi K3-256K  
**Fallback:** LongCat 2.5 Preview Free.

Use this only when repository context is large. Ask for a file map, entry points, dependencies, execution path and likely change surface. Kimi Code exposes dedicated coding models, including K3 variants, but access and allowance depend on the Kimi account/product route.[^7]

Do not ask for a rewrite during the mapping pass.
### Implement
**Model:** Ling 3.1 Flash Free  
**Hard-task fallback:** Kimi For Coding HighSpeed.

Give the approved specification and instruct the model to:

1. Inspect before editing.
2. State a short implementation plan.
3. Change only approved files.
4. Add or update tests.
5. Run validation commands.
6. Inspect `git diff`.
7. Report unresolved facts rather than inventing them.
### Review
**Model:** GPT OSS 120B on Groq  
**Fallback:** Nemotron 3 Ultra Free.

Provide the original specification plus the diff. Do not simply ask, “Is this good?” Require a severity-ranked audit:

- Requirement missed.
- Functional bug.
- Security issue.
- Regression risk.
- Unsupported claim.
- Unnecessary complexity.
- Missing test.
- Documentation mismatch.

Groq’s free plan is rate-limited by RPM, RPD, TPM and TPD; GPT OSS 120B currently has organization-level limits, so use it for the final diff rather than every small edit.[^8]
### Verify
**Model:** none initially.

Run the actual checks yourself:

```bash
git status
git diff --check
git diff --stat
git diff
# then project-specific build, lint, unit and integration tests
```

If a command fails, give **GPT OSS 120B** the command, complete error, relevant code and expected behavior. Do not ask it to “fix everything.”
### Document
**Model:** Gemini 3.8 Flash  
**Fallback:** Gemini Flash Latest.

Ask it to update only documentation affected by the implementation:

- What the component does.
- How to run it.
- Architecture and data flow.
- Tests and limitations.
- What was agent-assisted.

Gemini API limits are applied per project and tracked through RPM, TPM and RPD, so reserve full Flash for synthesis and use Flash-Lite for small cleanups.[^9]
## Project-specific routes
### C and C++ project
| Phase | Model | Instruction focus |
|---|---|---|
| Concept explanation | **Gemini 3.8 Flash** | POSIX behavior, ownership, lifetimes, UB and complexity |
| Design | **Nemotron 3 Ultra Free** | Invariants, interfaces, error paths and test strategy |
| Implementation | **Ling 3.1 Flash Free** | Minimal patch following current style |
| Compiler/debug review | **GPT OSS 120B** | Warnings, sanitizer output, Valgrind traces and edge cases |
| Modernization advice | **Gemini 3.8 Flash** | Contrast C99/C++98 with C11/C++17/20 without rewriting blindly |

Always require:

```text
Do not hide ownership, lifetime or synchronization decisions behind abstractions.
Explain every behavior that depends on POSIX, the C/C++ standard, or compiler extensions.
Compile with strict warnings and propose sanitizer/Valgrind checks where applicable.
```
### Portfolio or blog
| Phase | Model | Instruction focus |
|---|---|---|
| Content audit | **Gemini 3.8 Flash** | Accuracy, voice, duplication, stale claims and reader intent |
| Design-preserving edit | **Ling 3.1 Flash Free** | Edit existing HTML/CSS/JS without framework churn |
| Accessibility review | **GPT OSS 120B** | Semantics, keyboard access, focus, contrast and reduced motion |
| Final prose pass | **Gemini Flash Latest** | Remove generic AI language while preserving personal voice |

The site and blog should present a humble, lifelong exploration of software rather than borrowed expert status.
### Agent harness or control plane
| Phase | Model | Instruction focus |
|---|---|---|
| Requirements normalization | **Nemotron 3 Ultra Free** | Convert scattered documents into explicit contracts |
| Repository/component map | **Kimi K3-256K** | Services, gateways, state stores and control flow |
| Schema/API design | **Nemotron 3 Ultra Free** | Types, state transitions, idempotency and failure handling |
| Implementation | **Kimi For Coding HighSpeed** | Bounded phase or module, never the whole harness at once |
| Test generation | **Ling 3.1 Flash Free** | Unit, contract, integration and dry-run tests |
| Architecture audit | **GPT OSS 120B** | Contradictions, dead paths, coupling and missing observability |
| Documentation | **Gemini 3.8 Flash** | Diagrams, setup, operator runbook and limitations |

Maintain one source of truth. The existing harness work benefits from explicit state machines, scoped specialist roles, budget controls and validation gates; preserve that pattern instead of allowing agents to create parallel architectures.[^1][^2][^10]
### Authorized bug-bounty task
| Phase | Model | Instruction focus |
|---|---|---|
| Scope/rules extraction | **Gemini 3.8 Flash** | Exact in-scope assets, exclusions, rate limits and safe-harbor terms |
| Test-plan design | **Nemotron 3 Ultra Free** | Hypotheses, negative controls, evidence and stop conditions |
| Local evidence review | **Foundation-Sec-8B-Instruct Q4_K_M** | Redaction, suspicious commands, secrets and unsafe egress |
| Complex reasoning | **DeepSeek V4.1 Flash** when AMD quota is available | Analyze authorized evidence and defensive implications |
| Report drafting | **Gemini 3.8 Flash** | Reproduction, impact, evidence, limitations and remediation |
| Skeptical triage | **GPT OSS 120B** | Disprove the claim, find missing controls and challenge impact |

Mandatory guardrail:

```text
Operate only on explicitly authorized assets and within the supplied rules.
Do not infer permission from asset ownership or adjacency.
Stop before destructive, persistence, denial-of-service, credential-harvesting,
third-party or out-of-scope activity. Prefer dry-run and negative controls.
```
### IoT or embedded task
| Phase | Model | Instruction focus |
|---|---|---|
| System design | **Nemotron 3 Ultra Free** | Sensor, MCU, gateway, protocol, power and failure boundaries |
| Firmware implementation | **Ling 3.1 Flash Free** | One driver/state machine/module at a time |
| Protocol/backend | **Kimi For Coding HighSpeed** | MQTT/API/storage integration |
| Reliability review | **GPT OSS 120B** | Offline states, retries, watchdogs, calibration and safe actuation |
| Threat model | **DeepSeek V4.1 Flash** when available | Device identity, update chain, secrets and network exposure |
| Documentation | **Gemini 3.8 Flash** | Wiring, deployment, tests and field limitations |
## Reusable prompts
### Planning prompt
```text
Act as the planning specialist. Do not edit files.

Objective:
[one measurable outcome]

Source of truth:
[list files/docs]

Allowed scope:
[list files/components]

Non-goals:
[what must remain unchanged]

Inspect the available material and return:
1. current-state findings tied to real files,
2. assumptions and blocking questions,
3. a minimal phased plan,
4. per-file changes,
5. risks and rollback points,
6. acceptance criteria,
7. exact validation commands.

Prefer the smallest coherent implementation. Do not invent missing facts.
```
### Implementation prompt
```text
Implement the approved task below. Read all referenced files before editing.

[PASTE APPROVED SPEC]

Rules:
- Preserve unrelated behavior and the existing architecture.
- Modify only the approved scope.
- Do not invent URLs, credentials, metrics, APIs or requirements.
- Add or update tests for changed behavior.
- Use the repository’s existing conventions and dependencies.
- Stop and report if a requirement conflicts with the codebase.

Workflow:
1. Inspect and summarize the change plan in at most 10 bullets.
2. Implement; do not stop after planning.
3. Run the specified tests and linters.
4. Inspect git diff and correct accidental changes.
5. Report files changed, tests run, failures and remaining assumptions.
```
### Debugging prompt
```text
Diagnose one failure. Do not refactor unrelated code.

Expected behavior:
[expected]

Observed behavior:
[observed]

Reproduction command:
[command]

Complete error/log:
[verbatim output]

Relevant files:
[paths]

Return:
1. ranked root-cause hypotheses,
2. evidence for or against each,
3. the smallest justified patch,
4. a regression test,
5. validation commands.

If evidence is insufficient, request the exact missing observation instead of guessing.
```
### Review prompt
```text
Act as a skeptical reviewer, not the implementer.

Inputs:
- Original requirements: [paste/link]
- Current git diff: [provide]
- Test results: [provide]

Audit for:
- missed or contradicted requirements,
- functional defects and edge cases,
- security and privacy regressions,
- concurrency/resource-lifetime problems,
- unnecessary complexity,
- missing tests,
- stale or unsupported documentation.

Rank findings as blocker, high, medium or low. Cite the exact file and code.
Do not praise the work or rewrite it wholesale. Fix only confirmed blockers/high issues
if explicitly authorized; otherwise provide minimal patch guidance.
```
### Documentation/blog prompt
```text
Use the implementation and verified sources as the source of truth.
Write for an intermediate technical reader.

Voice:
- direct, grounded and specific,
- honest about limitations,
- no expert posturing,
- no corporate enthusiasm,
- no generic AI phrasing.

Separate:
- what was built,
- what was learned,
- what remains uncertain,
- what was implemented with agent assistance.

Do not claim benchmarks, compatibility, security or compliance without evidence.
```
## Stop rules
Stop the agent and reassess when it:

- Starts redesigning outside the requested scope.
- Creates new abstractions before understanding existing ones.
- Claims tests passed without showing commands/results.
- Invents filenames, URLs, benchmarks or credentials.
- Repeats the same failed fix twice.
- Touches more files than the approved plan without explanation.
- Replaces working dependencies or frameworks without a requirement.
- Treats lint success as functional proof.
- Uses “secure,” “production-ready,” “zero-trust” or “compliant” without evidence.
- Attempts live security actions without explicit scope and approval.

After two failed iterations, switch roles—not just models. Ask **GPT OSS 120B** to diagnose the evidence, then return a bounded patch to **Ling 3.1 Flash Free**.
## Context discipline
Give the agent only what it needs:

- **Small fix:** relevant function, failing test and error.
- **Feature:** approved specification, related modules and test conventions.
- **Architecture:** repository tree, current contracts and constraints.
- **Review:** requirements, diff and test output—not the entire brainstorming history.
- **Blog:** verified notes and sources—not raw speculative chats.

For large context, use **Kimi K3-256K** to produce a map or summary artifact first. Then give the implementer that artifact plus only the files required for the current phase.
## Quota discipline
OpenCode’s free Zen models are explicitly time-limited rather than permanently unlimited. Gemini applies rate limits per project rather than per API key, while Groq applies them at the organization level; rotating keys will not create independent quota pools.[^4][^9][^8]

Use this order when quota is tight:

1. **Foundation-Sec-8B-Instruct Q4_K_M locally** for private triage and safety checks.
2. **GPT OSS 20B** for small edits.
3. **Ling 3.1 Flash Free** for standard implementation.
4. **LongCat 2.5 Preview Free** for larger context.
5. **GPT OSS 120B** only for difficult debugging or final review.
6. **Gemini 3.8 Flash** for research/synthesis, not repetitive patch loops.
7. **Kimi For Coding HighSpeed** only when a task justifies its allowance.
## Final human checklist
```text
[ ] The result solves the original problem—not a larger imagined problem.
[ ] I understand the key design and code decisions.
[ ] I inspected every changed file.
[ ] The diff contains no credentials, generated junk or unrelated rewrites.
[ ] Tests were actually executed and their failures are documented.
[ ] Security/network actions stayed within explicit authorization.
[ ] Documentation matches the implementation.
[ ] Claims are calibrated and supported.
[ ] Agent-assisted work is disclosed where relevant.
[ ] The task is committed with a meaningful message.
[ ] Any follow-up became a separate issue instead of silently expanding scope.
```
## Default stack
When no special case applies:

```text
PLAN       → Nemotron 3 Ultra Free
MAP        → Kimi K3-256K only if the repository is large
IMPLEMENT  → Ling 3.1 Flash Free
DEBUG      → GPT OSS 120B
REVIEW     → GPT OSS 120B or Nemotron 3 Ultra Free
DOCUMENT   → Gemini 3.8 Flash
PRIVATE    → Foundation-Sec-8B-Instruct Q4_K_M via Ollama
```

The most important rule is simple: **one model proposes, another challenges, and the repository’s tests decide.**

---

## References

1. [summarize the general idea behind the harness and how it incorporates multiple projects into this one](https://www.perplexity.ai/search/a62f50a7-fa4a-4fb1-8528-c73e82cd474a) - The harness is a unified, autonomous bug bounty hunting platform that merges 9 separate security/AI ...

2. [You are a senior cybersecurity architect and AI systems engineer. Your task is to analyze the 9 repository   
  specification files and the master integration plan in the workspace to design a coherent, budget-friendly Bug 
  Bounty Harness.         ...

...                                                                 
    5. **Vulnerability State Transition Table**: A truth table mapping triage responses (e.g. successful proof   
  capture vs timeout) to state changes and subsequent pipeline events.](https://www.perplexity.ai/search/cab9638e-b472-4010-8412-137652ef9c20) - I've created a comprehensive technical design document for the unified Bug Bounty Harness. The docum...

3. [refine and incorporate these two prompts into one "You already have the scope. Reassess STORM-HUNT as a **bug-bounty-only** system and drop all CTF-related design, tooling, workflows, and cost assumptions.

## Goals

1. Remove every CTF-specific comp...

....

### Output requested
- a recommended schema for token tracking,
- a recommended schema for report state tracking,
- how these should connect to the RAG graph,
- the minimal implementation plan,
- and the highest-priority metrics to monitor first."](https://www.perplexity.ai/search/47f0a2b5-a507-4142-95f5-b509a8d0ed80) - Here is the fully unified, refined prompt incorporating both source prompts — the STORM-HUNT reasses...

4. [Zen](https://opencode.ai/docs/en/zen/) - Curated list of models provided by OpenCode.

5. [Ollama documentation - Ollama](https://docs.ollama.com/index) - Local models Download Ollama and run a model on your computer. Browse the model library for coding, ...

6. [Authentication - Ollama](https://docs.ollama.com/api/authentication) - The local API at http://localhost:11434 does not require authentication. To use cloud models, publis...

7. [www.kimi.com · code · docsModel Configuration | Kimi Code Docs](https://www.kimi.com/code/docs/en/kimi-code/models) - Kimi Code Documentation

8. [Rate Limits - GroqDocs - Groq Console](https://console.groq.com/docs/rate-limits) - Understand Groq API rate limits, headers, and best practices for managing request and token quotas i...

9. [Rate limits | Gemini API - Google AI for Developers](https://ai.google.dev/gemini-api/docs/rate-limits)

10. [Now I want to incorporate our latest Qwen3.8-27B conversation, and update the Bug Bounty Harness Orchestration and AI Gateway Specification](https://www.perplexity.ai/search/77a23f15-3978-4bf7-b0dd-e69d97eab852) - The specification is now updated to v2.1.2 and includes Qwen3.8‑27B Aggressive FastMTP as a new “LOC...

