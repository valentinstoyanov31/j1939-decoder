---
name: hint
description: Give a graduated hint for the current C++ challenge without writing the solution. Use when I say I'm stuck or ask for a hint.
argument-hint: "[what you're stuck on]"
---

## What I'm stuck on

$ARGUMENTS

## Instructions

Start by reading `docs/PROGRESS.md` to see where we are.

1. Look at my current code and any error output first (build or run the tests if
   useful) so the hint is about my actual problem, not a generic one.
2. Give the **smallest hint that could unblock me**, in this order of escalation:
   a. a question that points at the cause, or the name of the concept to look up;
   b. if I've already had (a) for this problem in this session: an explanation of the
      concept from an embedded C point of view, with a link;
   c. only if I'm still stuck after (b): a snippet of at most 10 lines that shows the
      idea on a *different* example, not my code.
3. Never write the full solution or edit my files. If I explicitly ask you to just
   write it, do so, and note it under "Concepts to revisit" in `docs/PROGRESS.md`.
4. If the problem is a compiler or CMake error, also explain how to read that kind of
   error message so I can solve the next one myself.
