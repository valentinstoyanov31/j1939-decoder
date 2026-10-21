# Progress

_Maintained by Claude after each review. Keep it short._

## Current

- **Challenge:** 0 — Repo skeleton
- **Status:** in progress — 3rd review 2026-10-21, verdict **revise** (local build ✅, CI/git ❌)
- **Started:** 2026-10-20

### Passed so far
- Static lib `j1939` with `PUBLIC` include dir; test links `PRIVATE`.
- C++20, extensions off; GoogleTest pinned to a commit via `FetchContent`.
- `constexpr std::string_view` instead of `#define`; version matches `project(VERSION 1.0)`.
- Root `ctest --test-dir build` finds and passes 1 test.
- `-Wall -Wextra -Wpedantic -Werror` on `j1939` and `test_version`, not on GoogleTest.

## Completed

_(none yet)_

## Open review points

1. **Blocking:** `src/`, `tests/`, `CMakeLists.txt`, `docs/` still untracked; `origin/main` has only README, .gitignore and an **empty** `.github/workflows/main.yml`.
2. **Blocking:** write the workflow (push + pull_request, checkout, configure/build/ctest with `--no-tests=error`), get it green, then red on purpose.
3. Warnings work but via order-dependent `add_compile_options`; move to `target_compile_options` (follow-up, not blocking).
4. Minor: CMP0135 dev warning, gmock built unused, no `.clang-format`, README is a title, `j1939_version` sits in the global namespace.

## Concepts to revisit

- CMake directory-scoped commands (`add_compile_options`, `enable_testing`) are **order-dependent**. Ordering now fixed; target-scoped options still to learn.
- Git basics: tracked vs untracked, what CI actually checks out.
