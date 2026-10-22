# Progress

_Maintained by Claude after each review. Keep it short._

## Current

- **Challenge:** 0 — Repo skeleton
- **Status:** in progress — 6th review 2026-10-22, verdict **revise** (one item left: red-on-purpose)
- **Started:** 2026-10-20

### Passed so far
- Static lib `j1939` with `PUBLIC` include dir; test links `PRIVATE`.
- C++20, extensions off; GoogleTest pinned to a commit via `FetchContent`.
- `constexpr std::string_view` instead of `#define`; version matches `project(VERSION 1.0)`.
- `enable_testing()` before `add_subdirectory(tests)` (root ctest found the test in review 3).
- Configure fix committed + pushed (`ad39de1`).
- CI workflow runs configure/build/ctest; run for `8895e0a` **green** (verified via GitHub API, step 8 success).

## Completed

_(none yet)_

## Open review points

1. **Blocking:** red-on-purpose not done yet. Earlier red runs (`26f1eae`, `7d5e9ea`) were an *invalid workflow file* (0 jobs), not a failing test. Break the test, push, see step 'test' fail, revert.
2. Workflow is still the demo template: remove echo steps, rename job/run-name, split configure/build/test into named steps, add `--no-tests=error`, pin `ubuntu-24.04`, `permissions: contents: read`. CLAUDE.md expects `ci.yml`.
3. Follow-up: warnings via order-dependent `add_compile_options`; move to target-based mechanism in challenge 1.
4. Minor: CMP0135 dev warning, gmock built unused, no `.clang-format`, README is a title, `j1939_version` in global namespace.
5. Suggested: GoogleTest fetch in `tests/` behind `BUILD_TESTING`; `target_compile_features`.

## Concepts to revisit

- CMake **targets are objects**: a `target_*` call needs the target to exist (like using a struct before its init). Ownership rule: the file that creates a target configures it.
- Directory scope vs target scope; variables flow down to subdirectories, not up.
- Usage requirements `PRIVATE`/`PUBLIC`/`INTERFACE` ≈ `.c`-only / both / header-only.
- Git ✅. CI: a red run must mean *your code* failed, not that the YAML is invalid. Check which step failed.
