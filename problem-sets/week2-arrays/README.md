# Week 2 — Arrays

Arrays, strings as arrays of characters, command-line arguments, and cryptography.

---

## Scrabble

Prompts two players for a word each and determines the winner based on Scrabble letter-point values, printing the winning player or announcing a tie.

Computes each word's score by iterating over its characters, looking up each letter's point value in a predefined array (indexed by letter, case-insensitive), and summing the totals for comparison.

**Concepts:** array lookups as a scoring table, case-insensitive character handling, comparing accumulated totals.

---

## Readability

Prompts the user for a block of text and estimates its reading level using the Coleman-Liau index, a formula based on the average number of letters and sentences per 100 words.

Counts letters, words, and sentences in a single pass through the input string, then applies the Coleman-Liau formula to compute a grade level, rounding and reporting it as a specific grade, "Before Grade 1," or "Grade 16+."

**Concepts:** iterating over a string as a character array, classifying characters (`isalpha`, `ispunct`), accumulating counts across a single pass.

---

## Substitution

Takes a 26-character substitution key as a command-line argument and uses it to encrypt user input, mapping each letter of the alphabet to the corresponding letter in the key while preserving case and leaving non-letters unchanged.

Validates the key for length (26 characters), that it contains only letters, and that no letter repeats. Encryption maps each input character to its substituted counterpart by calculating its offset from `a`/`A` and looking up that index in the key.

**Concepts:** command-line arguments (`argc`/`argv`), array indexing for character mapping, input validation, preserving case through arithmetic rather than separate logic paths.

---

## Reflections

This week leaned more on manipulating strings as arrays of characters rather than treating them as opaque values, and on validating input more rigorously before using it — both habits that carried forward well from the discipline C already requires elsewhere.
