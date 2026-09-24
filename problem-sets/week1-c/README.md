# Week 1 — C

Introduction to C: compiling, variables, conditionals, loops, and command-line arguments.

---

## Hello

Prompts the user for their name and prints a greeting. An entry point into C's syntax — variables, `printf`, and `get_string`.

**Concepts:** basic program structure, compiling with `make`, format specifiers.

---

## Mario (More Comfortable)

Prompts the user for a pyramid height (1–8) and prints two half-pyramids of `#` symbols side by side, separated by a gap, replicating the brick pyramids from Super Mario Bros.

Uses nested loops: an outer loop per row, inner loops for left-padding spaces, left-pyramid bricks, the gap, and right-pyramid bricks. For height `n`, row `i` (0-indexed) has `n - i - 1` leading spaces and `i + 1` bricks per side. Input is validated with a re-prompt loop until it falls within range.

**Concepts:** nested loops, input validation, translating a visual pattern into a mathematical relationship.

---

## Credit

Prompts the user for a credit card number and classifies it as **AMEX**, **MASTERCARD**, **VISA**, or **INVALID**, using card-prefix rules and Luhn's Algorithm.

Reads input with `get_long` (card numbers exceed `int` range) and extracts digits from the number arithmetically — `% 10` for the last digit, `/ 10` to drop it — rather than by string indexing. Implements Luhn's Algorithm: every other digit (from the second-to-last) is doubled, two-digit results are digit-summed, and the total is checked for a last digit of 0. Prefix and length checks then determine the card type.

**Concepts:** digit extraction via arithmetic instead of string slicing, integer truncation in division, position tracking with a counter.

---

## Reflections

Coming from Python, the main adjustment was the absence of high-level shortcuts — no string indexing, no comprehensions. Most problems that looked complex broke down into simple loops and arithmetic once solved on paper first.
