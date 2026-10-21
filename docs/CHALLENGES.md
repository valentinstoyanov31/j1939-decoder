# Challenges

One project, built up step by step: a small **J1939 library in C++20**. The core is
plain C++ that is built and tested on the PC, and is ported to an ST Nucleo-F303RE at
the end. Each challenge has a goal, requirements, the concepts it trains, and a clear
"done when". Challenges 3–7 are outlines; Claude expands them into a full spec (same
format as 0–2) when we get there.

| # | Challenge | Main C++ concepts |
|---|---|---|
| 0 | Repo skeleton: CMake, GoogleTest, CI | Build pipeline, targets, automated testing |
| 1 | CAN ID decoder (priority, PGN, source address) | Structs, `constexpr`, `static_assert`, bit manipulation |
| 2 | SPN extraction from frames | `std::array`, `std::span`, endianness, `std::optional`, `enum class` |
| 3 | Fixed-capacity ring buffer, no heap | Class templates, RAII, copy/move rules, sanitizers in CI |
| 4 | PGN message dispatcher | Lambdas, callback cost trade-offs, fixed tables |
| 5 | Hardware abstraction + mock CAN driver | Concepts, dependency injection, mocking |
| 6 | Transport protocol (BAM) reassembly | State machines, `enum class`, `std::variant` |
| 7 | Port to the Nucleo-F303RE | Cross-compiling, CMake toolchain files, CI for host + target |

---

## Challenge 0 — Repo skeleton

**Goal:** an empty-but-professional project that builds, runs tests and checks itself
on every push.

**Suggested layout**

```
j1939-cpp/
├── CMakeLists.txt
├── src/
│   ├── CMakeLists.txt
│   ├── include/j1939/version.hpp
│   └── version.cpp
├── tests/
│   ├── CMakeLists.txt
│   └── test_version.cpp
├── .github/workflows/ci.yml
├── .clang-format
├── .gitignore
└── README.md
```

**Requirements**

- CMake 3.20 or newer, C++20 required, compiler extensions off (`CMAKE_CXX_EXTENSIONS OFF`).
- A static library target `j1939` built from `src/`, separate from the tests.
- One trivial function, e.g. `std::string_view j1939::version()`, plus a GoogleTest test for it.
- GoogleTest pulled in with `FetchContent`; tests registered in CTest with `gtest_discover_tests`.
- Strict warnings on your own targets only: `-Wall -Wextra -Wpedantic -Werror`. Not on GoogleTest.
- A GitHub Actions workflow that, on every push and pull request, configures, builds
  and runs `ctest --output-on-failure` on Ubuntu.

**Done when**

- `cmake -S . -B build && cmake --build build && ctest --test-dir build` passes locally.
- CI is green on GitHub.
- You deliberately broke the test once, pushed, and watched CI turn red.

**Stretch:** GCC + Clang CI matrix; `CMakePresets.json`; CI badge in the README.

**Trains:** target-based CMake (`target_link_libraries`, `target_include_directories`,
`PUBLIC` vs `PRIVATE`), out-of-source builds, library vs test targets.

**Reference:** <https://google.github.io/googletest/quickstart-cmake.html>

---

## Challenge 1 — CAN ID decoder

**Goal:** turn a 29-bit extended CAN identifier into its J1939 fields, and back.

**Requirements**

- A struct holding priority (3 bits), PGN (18 bits), source address (8 bits), and the
  destination address for PDU1 messages.
- A `constexpr` decode function from `std::uint32_t` and a `constexpr` encode function
  back to `std::uint32_t`.
- Handle PDU1 (PF < 240: PS is a destination address, not part of the PGN) and PDU2
  (PF ≥ 240: PS is part of the PGN).
- Reject identifiers that don't fit in 29 bits. Decide yourself how (e.g. `std::optional`)
  and be ready to explain the choice.
- Prove at least two decodings at compile time with `static_assert`.
- GoogleTest cases at least for:
  - `0x0CF00400` (EEC1): priority 3, PGN `0xF004`, SA `0x00`
  - `0x18EAFF00` (Request): priority 6, PGN `0xEA00`, DA `0xFF`, SA `0x00`
  - encode → decode round trip
  - an identifier wider than 29 bits

**Done when:** all tests pass locally and in CI, no warnings, and the decoder has no
magic numbers left unnamed.

**Trains:** structs and aggregate initialisation, `constexpr`/`static_assert`,
bit masks and shifts on unsigned types, `std::optional`, naming constants with
`constexpr` instead of `#define`.

---

## Challenge 2 — SPN extraction

**Goal:** read physical values out of an 8-byte J1939 data field.

**Requirements**

- Take the data as `std::span<const std::uint8_t, 8>`.
- J1939 data is little-endian. Assemble multi-byte values without UB.
- Implement at least:
  - SPN 190, engine speed (EEC1, PGN 61444): bytes 4–5 (1-based), 0.125 rpm/bit, offset 0
  - SPN 110, coolant temperature (ET1, PGN 65262): byte 1, 1 °C/bit, offset −40 °C
- Respect the J1939 special ranges. For 1-byte values: 0–250 valid, 254 = error,
  255 = not available. For 2-byte values: 0x0000–0xFAFF valid, 0xFExx = error,
  0xFFxx = not available. The caller must be able to tell valid, error and
  not-available apart (an `enum class` status plus value is one option; justify yours).
- Bonus: one generic, reusable description of an SPN (start byte, length, scale,
  offset) so new SPNs are a single line, not a new function.
- Tests for valid values, boundaries (250/251, 0xFAFF/0xFB00), error and not-available.

**Done when:** tests pass locally and in CI; adding a new 1- or 2-byte SPN takes one line.

**Trains:** `std::span` (fixed extent), endianness, `std::optional` / status types,
`enum class`, templates or `constexpr` structs as data descriptions.

---

## Challenge 3 — Ring buffer (outline)

Fixed-capacity, single-producer/single-consumer ring buffer for CAN frames, as a class
template `RingBuffer<T, N>`. No heap. Decide and test copy/move behaviour (rule of 0/5).
Add AddressSanitizer + UndefinedBehaviorSanitizer to a CI job. Stretch: make it safe
for one ISR producer and one main-loop consumer with `std::atomic`.

## Challenge 4 — PGN dispatcher (outline)

Register handlers per PGN in a fixed-size table and dispatch incoming frames to them.
Compare function pointers, a small fixed-capacity callable, and `virtual` interfaces;
measure or reason about the cost of each. No `std::function` in the library (explain why).

## Challenge 5 — Hardware abstraction + mock (outline)

Define a C++20 `concept` for a CAN driver (send/receive). Write a mock driver for tests
and a SocketCAN driver for Linux (`vcan0`). The J1939 node is a template over the
driver, so there is no `virtual` dispatch and the tests use the mock.

## Challenge 6 — Transport protocol BAM (outline)

Reassemble multi-packet broadcast messages (TP.CM BAM + TP.DT, up to 1785 bytes) as an
explicit state machine with `enum class` states. Handle timeouts, out-of-order and
aborted sequences. Consider `std::variant` for events.

## Challenge 7 — Port to the Nucleo-F303RE (outline)

CMake toolchain file for `arm-none-eabi-gcc`, build the same `j1939` library for the
Cortex-M4 with `-fno-exceptions -fno-rtti`, link a minimal firmware that decodes
frames from the bxCAN peripheral. CI builds both host (tests) and target (firmware).
Compare flash/RAM usage with `arm-none-eabi-size`.
