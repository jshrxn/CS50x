# Week 0 — Scratch: Password Fortress

## Description

A terminal-style Scratch game where the player types in a password and the game evaluates its strength in real time. The program scans the password character by character, checking for a minimum length, the presence of at least one number, one uppercase letter, and one symbol. Each check feeds into a score, which determines whether the password is classified as **Weak**, **Medium**, or **Strong**.

The project uses two sprites: a **Terminal** sprite that handles input, scanning, and scoring, and an **Oracle** sprite that reacts to the result via broadcast messages — giving the game a bit of personality beyond a flat pass/fail output.

## How it works

- The player is prompted to enter a password.
- The program loops through the password one character at a time using a custom block, checking each character against number/uppercase/symbol conditions.
- Boolean flags (`lengthOK`, `hasNumber`, `hasUpper`, `hasSymbol`) track which conditions were met.
- These flags combine into a `score`, which maps to a `strength` rating.
- The result is broadcast to the Oracle sprite, which responds accordingly.

## What I learned

- How to break repeated logic into a **custom block with a parameter** instead of duplicating checks.
- Using a loop to scan a string character-by-character (`letter_of` + an index variable) rather than checking it all at once.
- Coordinating multiple sprites using **broadcasts**, so logic and reaction aren't crammed into a single sprite.
- Translating programming concepts from Python (CS50P) into Scratch's block-based, event-driven model.

## Design Choices

Kept the aesthetic minimal and terminal-inspired — a dark backdrop with a single output "terminal" sprite — to keep the focus on the logic (loops, conditionals, custom blocks) rather than visual polish, in line with what week0 is meant to assess.
