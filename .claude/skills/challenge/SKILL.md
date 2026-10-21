---
name: challenge
description: Show the current C++ learning challenge, or a specific one by number, with its requirements and done-when criteria.
argument-hint: "[challenge-number]"
disable-model-invocation: true
---

## Instructions

Start by reading `docs/PROGRESS.md` to see where we are.

Requested challenge: "$ARGUMENTS" (empty means: the current challenge in `docs/PROGRESS.md`).

1. Read `docs/CHALLENGES.md` and find the requested challenge.
2. If it is only an outline (challenges 3–7), expand it into a full spec in the same
   format as challenges 0–2 (goal, requirements, done when, stretch, trains), write
   that expansion back into `docs/CHALLENGES.md`, and tell me you did.
3. Present the challenge to me clearly. Do not include solution code.
4. If this is a new challenge, set it as current in `docs/PROGRESS.md` with status
   "in progress" and today's date.
5. Finish with one short line: what concept to read up on first, with a
   cppreference.com or learncpp.com link where useful.
