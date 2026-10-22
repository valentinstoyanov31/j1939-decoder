# Progress

_Maintained by Claude after each review. Keep it short._

## Current

- **Challenge:** 0 — Repo skeleton
- **Status:** in progress — 5th review 2026-10-22, verdict **revise** (local OK; fix not committed, CI empty)
- **Started:** 2026-10-20

### Passed so far
- Static lib `j1939` with `PUBLIC` include dir; test links `PRIVATE`.
- C++20, extensions off; GoogleTest pinned to a commit via `FetchContent`.
- `constexpr std::string_view` instead of `#define`; version matches `project(VERSION 1.0)`.
- `enable_testing()` before `add_subdirectory(tests)` (root ctest found the test in review 3).
- Project committed and pushed (`7d5e9ea`).

## Completed

_(none yet)_

## Open review points

1. **Blocking:** local `CMakeLists.txt` reverted to the working `add_compile_options` version (builds, 1/1 pass, flags correct) but it's **uncommitted**; `origin/main` (`7d5e9ea`) still fails to configure.
2. **Blocking:** `.github/workflows/main.yml` is still empty. Write it (push + PR, checkout, configure/build/`ctest --no-tests=error`), green, then red on purpose.
3. Follow-up: warnings are still order-dependent `add_compile_options`; move to a target-based mechanism (function or `INTERFACE` lib) in `src/`/`cmake/`, ideally in challenge 1.
4. Minor: CMP0135 dev warning, gmock built unused, no `.clang-format`, README is a title, `j1939_version` in global namespace.
5. Suggested (not required): GoogleTest fetch in `tests/` behind `BUILD_TESTING`, `target_compile_features` instead of global `CMAKE_CXX_STANDARD`.

## Concepts to revisit

- CMake **targets are objects**: a `target_*` call needs the target to exist (like using a struct before its init). Ownership rule: the file that creates a target configures it.
- Directory scope vs target scope; variables flow down to subdirectories, not up.
- Usage requirements `PRIVATE`/`PUBLIC`/`INTERFACE` ≈ `.c`-only / both / header-only.
- Git: done ✅ (committed + pushed). Next: verify CI actually runs.
