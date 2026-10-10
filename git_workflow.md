# 🛠️ PORTFOLIO Repository Architecture & Git Submodule Workflow Guide

This document is your complete guide to managing the **PORTFOLIO** workspace. It explains how the umbrella repository functions, how submodules interact with parent commits, and how to resolve common submodule issues (such as detached HEADs, permission errors, and state divergence).

---

## 1. Repository Architecture Overview

Your `PORTFOLIO` workspace operates as an **Umbrella Container Repository** tracking both standalone project folders and independent Git Submodules, separated by build style.

```
PORTFOLIO/ (Main Git Repository -> git@github.com:On-Off-Grid/PORTFOLIO.git)
├── 📄 README.md, git_workflow.md, ROADMAP_2026.md, AI_Task-Start_Cheat_Sheet.md, .gitignore, .gitmodules
├── 📂 site/                                (portfolio website, tracked here; published with
│   │                                       git subtree push --prefix site -> On-Off-Grid/souhail-portfolio)
├── 📂 From_scratch/                        (hand-written 42 projects)
│   ├── 📂 Core Project Folders (Directly tracked in PORTFOLIO)
│   │   ├── cub3d/
│   │   ├── fractol/
│   │   ├── minishell/
│   │   ├── minitalk/
│   │   └── readmes/
│   └── 📦 Git Submodules (Independent Git Repositories tracked via commit pointers)
│       ├── CPPS/                          -> git@github.com:On-Off-Grid/CPPS.git
│       ├── inception/                     -> git@github.com:On-Off-Grid/inception.git
│       ├── minilibx-linux/                -> git@github.com:42Paris/minilibx-linux.git
│       ├── my_irc/                        -> git@github.com:On-Off-Grid/shared_irc.git
│       ├── Patterns-in-code-and-culture/  -> git@github.com:On-Off-Grid/Patterns-in-code-and-culture.git
│       └── philosophers/                  -> git@github.com:On-Off-Grid/Dining_Philosophers.git
└── 🤖 Vibe_coded/                          (AI-assisted projects — each a STANDALONE repo,
    │                                       git-ignored by the umbrella; no submodule pointers)
    ├── IgranSense_MVP/                    -> git@github.com:On-Off-Grid/IgranSense_MVP.git
    ├── harness/                           -> git@github.com:On-Off-Grid/harness.git
    └── Ult_harness/                       -> git@github.com:On-Off-Grid/Ult_harness.git
```

---

## 2. The 2-Step Submodule Workflow (Must-Follow Rule)

Because submodules are independent Git repositories inside your umbrella workspace, making a change to a submodule requires **two distinct steps**:

```
 ┌──────────────────────────────────────────────────────────┐
 │ Step 1: Commit & Push inside the Submodule               │
 │ (Updates the submodule's own Git repository)            │
 └────────────────────────────┬─────────────────────────────┘
                              │
                              ▼
 ┌──────────────────────────────────────────────────────────┐
 │ Step 2: Commit & Push inside the Umbrella PORTFOLIO      │
 │ (Updates the commit pointer tracked by PORTFOLIO)       │
 └──────────────────────────────────────────────────────────┘
```

### Complete Example Walkthrough

If you modify code inside `CPPS`:

#### Step 1: Commit & Push inside the Submodule
```bash
# 1. Move into the submodule directory
cd /home/souhail/Desktop/Desktop/PORTFOLIO/From_scratch/CPPS

# 2. Ensure you are on a branch (e.g. main), NOT in a detached HEAD
git checkout main

# 3. Stage, commit, and push your work to the submodule's remote
git add .
git commit -m "feat(cpp08): update Span template logic"
git push origin main
```

#### Step 2: Update the Umbrella `PORTFOLIO` Pointer
```bash
# 1. Return to the root PORTFOLIO directory
cd /home/souhail/Desktop/Desktop/PORTFOLIO

# 2. Check root status (git will report: modified: CPPS (new commits))
git status

# 3. Stage the new commit pointer of the submodule
git add From_scratch/CPPS

# 4. Commit and push the umbrella update to GitHub
git commit -m "chore: update CPPS submodule reference to latest commit"
git push origin main
```

### The Post-Change Sync Ritual (run after EVERY submodule change)

Any edit under a submodule directory — code, docs, tests, even a quick fix —
leaves the umbrella pointing at a commit that GitHub does not know about until
you complete **all four steps**. Run them in this order, every time:

```bash
# ── 0. Pre-check: be on a branch, never a detached HEAD ─────────────────────
cd /home/souhail/Desktop/Desktop/PORTFOLIO/From_scratch/<submodule>
git status -sb                    # must show "## main...origin/main", not "HEAD detached"
git checkout main                 # if detached: git checkout main

# ── 1. Inside the submodule: commit AND push first ──────────────────────────
git add -A
git commit -m "feat(<submodule>): describe the change"
git push origin main              # push must succeed BEFORE step 2

# ── 2. Umbrella: advance the commit pointer ─────────────────────────────────
cd /home/souhail/Desktop/Desktop/PORTFOLIO
git status                        # expect: modified: From_scratch/<submodule> (new commits)
git add From_scratch/<submodule>
git commit -m "chore: bump <submodule> pointer to <short-sha>"
git push origin main

# ── 3. Verify everything is in sync ─────────────────────────────────────────
git submodule status              # leading space = clean; "+"/"-" = out of sync
git status --short                # expect: clean
```

**Order matters.** If you commit the umbrella pointer (step 2) before the
submodule push (step 1) succeeds, every fresh clone — including GitHub's —
records a commit that does not exist on the submodule remote, and
`git clone --recurse-submodules` breaks for everyone, yourself included.

**Step 4 — republish the site when the change is site-facing:**

If the submodule change affects anything the portfolio links to or quotes
(project card links, evidence lines, readmes, live content), re-run the site
publish ritual:

```bash
# Link audit first (every external URL must return 200)
# then publish:
cd /home/souhail/Desktop/Desktop/PORTFOLIO
git subtree push --prefix site git@github.com:On-Off-Grid/souhail-portfolio.git main
# Verify: https://on-off-grid.github.io/souhail-portfolio/ serves the change
```

**`Vibe_coded/` is different:** those repos (`IgranSense_MVP`, `harness`,
`Ult_harness`) are **git-ignored standalones, not submodules** — there is no
pointer to advance. You only `git push` inside the repo itself (plus the site
republish above if the site references it).

---

## 3. Resolving Common Submodule Issues & Friction

### Issue A: "Detached HEAD" inside a Submodule
**Symptom**: When you run `git status` inside a submodule, it says `HEAD detached at <commit_hash>`. Any commits made here won't belong to `main` and might be lost when updating.

**Solution**:
Before making edits inside any submodule, make sure you switch to `main`:
```bash
cd From_scratch/CPPS
git checkout main
```

---

### Issue B: Private vs. Public Submodules & Remote URL Mismatches
**Symptom**: You changed a submodule's visibility on GitHub (e.g. Private to Public) or changed its repository name, but cloning or fetching fails with `Repository not found` or `Permission denied`.

**Solution**:
1. Update the URL in `.gitmodules` at the root of `PORTFOLIO`.
2. Sync the configuration across Git with:
   ```bash
   git submodule sync --recursive
   ```
3. Update the tracking:
   ```bash
   git submodule update --remote --merge
   ```

---

### Issue C: Permission Denied on Third-Party Submodules (`minilibx-linux`)
**Symptom**: You commit changes locally inside `minilibx-linux`, but `git push` fails with:
`ERROR: Permission to <owner>/<repo>.git denied to On-Off-Grid.`

**Why this happens**: The submodule remote URL points to someone else's GitHub account (e.g., `42Paris/minilibx-linux.git`).

> **Note**: `my_irc` used to live here (it pointed at `abareich/ft_irc.git`).
> It was migrated to your own repository `On-Off-Grid/shared_irc` in October 2026 —
> see **Issue E** below for the recipe. `minilibx-linux` is now the only third-party submodule.

**Solution Options**:
- **Option 1 (Recommended)**: Fork the repository to your own GitHub account, then update `.gitmodules` (or re-point the submodule, see Issue E) and run `git submodule sync`.
- **Option 2**: If you only need to store changes in your `PORTFOLIO` umbrella, you can commit the submodule pointer locally in `PORTFOLIO` without pushing to the third-party remote. **Caveat**: local-only commits are fragile — back them up first (Issue E, step 0).

---

### Issue D: Divergence / Diffs between Submodule and Umbrella
**Symptom**: `git status` in `PORTFOLIO` shows `modified: <submodule> (new commits)` or `modified: <submodule> (untracked content)`.

**Sanity Check & Unification Command**:
Run this command from `/home/souhail/Desktop/Desktop/PORTFOLIO` to inspect and unify all submodules at once:

```bash
# Check status of root + all submodules
git submodule status

# To pull latest updates for all submodules simultaneously:
git submodule update --remote --merge

# To stage all updated submodule pointers in PORTFOLIO:
git add .
git commit -m "chore: synchronize all submodule pointers with remote main"
git push origin main
```

---

### Issue E: Re-pointing a Submodule to a Different Remote (worked example: `my_irc` → `shared_irc`)

**Symptom**: A submodule's remote is wrong, dead, or belongs to someone else, and
the history in your working copy does not exist anywhere else (e.g. it was never
pushed because you had no rights). A plain URL edit in `.gitmodules` is **not**
enough — a divergent local history would be silently discarded.

**The safe migration recipe:**

```bash
# ── 0. BACK UP local-only history first ─────────────────────────────────────
#    (push the local HEAD to your own repo under a backup branch — or make a
#     `git bundle` if you have no suitable remote)
cd From_scratch/my_irc
git push git@github.com:On-Off-Grid/shared_irc.git HEAD:refs/heads/backup/umbrella-my_irc-<sha>
git ls-remote git@github.com:On-Off-Grid/shared_irc.git "refs/heads/backup/*"   # confirm

# ── 1. Remove the old submodule (unregister + delete working tree) ──────────
cd /home/souhail/Desktop/Desktop/PORTFOLIO
git submodule deinit -f From_scratch/my_irc
git rm -f From_scratch/my_irc
rm -rf .git/modules/my_irc            # clear the migrated gitdir leftover

# ── 2. Re-add from the new remote (same path keeps every reference valid) ───
git submodule add git@github.com:On-Off-Grid/shared_irc.git From_scratch/my_irc
cd From_scratch/my_irc && git status -sb   # must show "## main" on the NEW remote

# ── 3. Sweep + verify ───────────────────────────────────────────────────────
grep -ri "abareich" .gitmodules site/   # expect: no hits (only this doc cites it historically)
grep -rn "shared_irc" site/index.html   # card must point at the new repo
git submodule status                    # clean pointer, no +/-/U
```

**October 2026 migration record**: `From_scratch/my_irc` was re-homed from
`git@github.com:abareich/ft_irc.git` (third-party, local commit `0ca146f` unpushable)
to the original repo `git@github.com:On-Off-Grid/shared_irc.git`. The local snapshot
was preserved as branch `backup/umbrella-my_irc-0ca146f` on `shared_irc`.
The portfolio's my_irc card was re-pointed to the new repo and the site was
republished (sync ritual, step 4).

---

## 4. Quick Reference Cheat Sheet

| Task | Command |
| :--- | :--- |
| **Clone repo with all submodules** | `git clone --recurse-submodules git@github.com:On-Off-Grid/PORTFOLIO.git` |
| **Check all submodules status** | `git submodule status` |
| **Sync remote URLs after `.gitmodules` edits** | `git submodule sync` |
| **Update all submodules to latest remote HEAD** | `git submodule update --remote --merge` |
| **Un-stick detached HEAD in a submodule** | `cd <submodule> && git checkout main` |
| **Stage updated submodule pointer in root** | `cd PORTFOLIO && git add <submodule_name>` |
| **After ANY submodule change (full sync ritual)** | ① `cd <submodule> && git push origin main` → ② `cd PORTFOLIO && git add <submodule> && git commit -m "chore: bump <submodule> pointer" && git push` → ③ `git submodule status` (clean) |
| **Republish the site after site-facing changes** | `git subtree push --prefix site git@github.com:On-Off-Grid/souhail-portfolio.git main` |
| **Back up a submodule's local-only history** | `cd <submodule> && git push <own-repo-url> HEAD:refs/heads/backup/<name>-$(git rev-parse --short HEAD)` |
| **Re-point a submodule to a new remote** | See **Issue E**: backup → `git submodule deinit -f <path>` → `git rm -f <path>` → `git submodule add <new-url> <path>` |
