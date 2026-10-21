---
name: review
description: Build, test and review my work on the current C++ challenge like a senior embedded C++ colleague, then update docs/PROGRESS.md.
argument-hint: "[optional focus, e.g. tests or cmake]"
disable-model-invocation: true
allowed-tools: Bash(cmake *) Bash(ctest *) Bash(git status *) Bash(git diff *) Bash(git log *)
---

## Instructions

Start by reading `docs/PROGRESS.md` to see where we are.

Extra focus requested: "$ARGUMENTS"

1. Run `git status --short` and `git log --oneline -10`, then read the current challenge
   in `docs/CHALLENGES.md` and all files I changed for it.
2. Do a clean build and run the tests yourself:
   `cmake -S . -B build-review && cmake --build build-review && ctest --test-dir build-review --output-on-failure`.
   Report the result honestly, including warnings.
3. Check every requirement and "done when" item of the challenge. For each, mark it
   ✅ met, ⚠️ partly, or ❌ missing, with one line of evidence. CI being green is
   something I confirm; ask me if you can't see it.
4. Review the code in this order, most important first:
   - **Correctness and undefined behaviour** (overflow, aliasing, lifetime, shifts on
     signed types, uninitialised values)
   - **Tests**: do they test boundaries and failure cases, or only the happy path?
   - **Embedded suitability**: heap use, exceptions, hidden runtime cost, code size
   - **Modern C++ style**: `constexpr`, `const`, `enum class`, `std::span`, naming
   - **Build system**: target-based CMake, warning flags scoped correctly
5. For each finding: file and line, what's wrong, *why* it matters (an interviewer's
   angle is welcome), and a hint at the fix. **Don't rewrite my code** and don't edit
   files in `src/`, `tests/`, `CMakeLists.txt` or `.github/`.
6. End with a verdict: **pass** (move on), **pass with follow-ups**, or **revise**, and
   name the one thing I did best.
7. Update `docs/PROGRESS.md`: status, open review points (short), concepts I
   struggled with. If the verdict is pass, move the challenge to "Completed" and set
   the next one as current with status "not started".
