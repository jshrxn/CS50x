# Week 3 — Algorithms

Algorithmic efficiency, searching, sorting, and recursion.

---

## Sort

A short exercise identifying which of three given sorting algorithm implementations is bubble sort, selection sort, or merge sort, based on their measured running times on datasets of increasing size — reasoning from algorithmic complexity (O(n²) vs. O(n log n)) rather than reading the code directly.

**Concepts:** relating Big O time complexity to real, measurable performance differences.

---

## Plurality

Simulates a plurality vote: given a list of candidates and a series of votes, tallies each candidate's total and prints the winner (or all tied winners, if applicable).

Stores vote counts in an array parallel to the candidates array, incrementing the matching candidate's count per vote, then scans for the maximum to determine the winner(s).

**Concepts:** parallel arrays, linear search for matching input, tracking a running maximum.

---

## Tideman

Implements a Tideman (ranked-pairs) election: voters rank candidates by preference, and the winner is determined by comparing every pair of candidates head-to-head, ranking those pairs by strength of victory, then "locking in" pairs into a directed graph — skipping any pair that would create a cycle — to produce a definitive winner.

Tracks preferences in a 2D array (how often each candidate is preferred over each other), generates every possible pair, sorts pairs by strength of victory, then locks each pair in order unless doing so would create a cycle (checked recursively by following the graph of already-locked edges). The winner is the candidate with no incoming edges in the final locked graph.

**Concepts:** 2D arrays for pairwise relationships, custom sort comparators, recursion for cycle detection, reasoning about a directed graph without an explicit graph data structure.

---

## Reflections

Week 3 marked a shift from "translate logic into C" toward "design the algorithm itself." Sort was a warm-up in reasoning about performance from behavior alone — recognizing an algorithm's complexity by its symptoms rather than reading its code. Plurality reinforced basic array/tallying patterns. Tideman, chosen deliberately over the more comfortable Runoff option, was where the week's real thinking lived: breaking a real-world voting method down into pairwise comparisons, a custom sort by strength of victory, and recursive cycle detection in `lock_pairs` — the point where recursion stopped being an abstract concept and became the only practical way to answer "does locking this edge eventually lead back to itself." Altogether, the week was less about new C syntax and more about structuring a non-trivial problem before writing any code at all.
