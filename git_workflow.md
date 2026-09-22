# 🛠️ PORTFOLIO Repository Architecture & Git Submodule Workflow Guide

This document is your complete guide to managing the **PORTFOLIO** workspace. It explains how the umbrella repository functions, how submodules interact with parent commits, and how to resolve common submodule issues (such as detached HEADs, permission errors, and state divergence).

---

## 1. Repository Architecture Overview

Your `PORTFOLIO` workspace operates as an **Umbrella Container Repository** tracking both standalone project folders and independent Git Submodules.

```
PORTFOLIO/ (Main Git Repository -> git@github.com:On-Off-Grid/PORTFOLIO.git)
├── 📄 README.md, git_workflow.md, ROADMAP_2026.md, .gitignore, .gitmodules
├── 📂 Core Project Folders (Directly tracked in PORTFOLIO)
│   ├── cub3d/
│   ├── fractol/
│   ├── minishell/
│   ├── minitalk/
│   └── readmes/
└── 📦 Git Submodules (Independent Git Repositories tracked via commit pointers)
    ├── CPPS/                          -> git@github.com:On-Off-Grid/CPPS.git
    ├── inception/                     -> git@github.com:On-Off-Grid/inception.git
    ├── minilibx-linux/                -> git@github.com:42Paris/minilibx-linux.git
    ├── my_irc/                        -> git@github.com:abareich/ft_irc.git
    ├── Patterns-in-code-and-culture/  -> git@github.com:On-Off-Grid/Patterns-in-code-and-culture.git
    └── philosophers/                  -> git@github.com:On-Off-Grid/Dining_Philosophers.git
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
cd /home/souhail/Desktop/Desktop/PORTFOLIO/CPPS

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
git add CPPS

# 4. Commit and push the umbrella update to GitHub
git commit -m "chore: update CPPS submodule reference to latest commit"
git push origin main
```

---

## 3. Resolving Common Submodule Issues & Friction

### Issue A: "Detached HEAD" inside a Submodule
**Symptom**: When you run `git status` inside a submodule, it says `HEAD detached at <commit_hash>`. Any commits made here won't belong to `main` and might be lost when updating.

**Solution**:
Before making edits inside any submodule, make sure you switch to `main`:
```bash
cd CPPS
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

### Issue C: Permission Denied on Third-Party Submodules (`my_irc` or `minilibx-linux`)
**Symptom**: You commit changes locally inside `my_irc` or `minilibx-linux`, but `git push` fails with:
`ERROR: Permission to <owner>/<repo>.git denied to On-Off-Grid.`

**Why this happens**: The submodule remote URL points to someone else's GitHub account (e.g., `abareich/ft_irc.git` or `42Paris/minilibx-linux.git`).

**Solution Options**:
- **Option 1 (Recommended)**: Fork the repository to your own GitHub account (`On-Off-Grid/ft_irc.git`), then update `.gitmodules` and run `git submodule sync`.
- **Option 2**: If you only need to store changes in your `PORTFOLIO` umbrella, you can commit the submodule pointer locally in `PORTFOLIO` without pushing to the third-party remote.

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

## 4. Quick Reference Cheat Sheet

| Task | Command |
| :--- | :--- |
| **Clone repo with all submodules** | `git clone --recurse-submodules git@github.com:On-Off-Grid/PORTFOLIO.git` |
| **Check all submodules status** | `git submodule status` |
| **Sync remote URLs after `.gitmodules` edits** | `git submodule sync` |
| **Update all submodules to latest remote HEAD** | `git submodule update --remote --merge` |
| **Un-stick detached HEAD in a submodule** | `cd <submodule> && git checkout main` |
| **Stage updated submodule pointer in root** | `cd PORTFOLIO && git add <submodule_name>` |
