# Week 5 — Data Structures

Dynamic memory and abstract data types: recursive structures on the heap, hash tables with separate chaining, and the cost of organizing data in memory.

---

## Inheritance

A simulation of blood-type inheritance across three generations. Each person is a heap-allocated `person` struct holding pointers to two parents and two alleles (`A`, `B`, or `O`), so the family is a binary tree built, printed, and freed recursively.

- **`create_family`:** allocates a person, then recurses to create two parents one generation up. The oldest generation, which has no parents, receives two randomly generated alleles via `random_allele`. Every other person inherits one randomly selected allele from each parent. Allocation failures are handled at each level: if a later allocation fails, everything already built is freed before returning `NULL`, so a partial tree is never leaked.
- **`print_family`:** prints the tree recursively, indenting by generation and labeling each person as Child, Parent, Grandparent, or Great-Grandparent with the appropriate number of "Great-" prefixes.
- **`free_family`:** frees the tree in post-order, releasing both parents before the child, so no node is freed while still reachable through another pointer.

**Concepts:** self-referential structs, binary tree structure, recursion with explicit base cases, pointer wiring, `malloc` failure handling, post-order deallocation, pseudo-random selection with `random`.

---

## Speller

A spell checker built on a hash table. The program loads a dictionary into memory, then reads a text file and reports every word that does not appear in the dictionary, along with the time spent in each phase (`load`, `check`, `size`, `unload`).

- **`load`:** reads the dictionary word by word with `fscanf`, allocates one node per word, and inserts it at the head of its bucket's linked list in constant time. Failure to open the file or to allocate a node is handled, and on allocation failure everything already loaded is released before returning `false`.
- **`hash`:** a polynomial string hash. Each character is lowercased and folded in as `hash = hash * 31 + c`, so character position affects the result, and the final value is reduced modulo the number of buckets. Lowercasing inside the hash guarantees that a word and its differently capitalized forms land in the same bucket.
- **`check`:** hashes the word, then walks the corresponding bucket's linked list comparing with `strcasecmp`, making lookups case-insensitive.
- **`size`:** returns a running word count maintained by `load`.
- **`unload`:** traverses every bucket, saving each node's `next` pointer before freeing the node, then resets each bucket to `NULL` and the word count to zero.

Collisions are resolved by separate chaining: each bucket holds a linked list of the words that hash to it. Lookup cost is therefore proportional to chain length, which is set by the number of buckets and the distribution of the hash function.

**Concepts:** hash tables, separate chaining, singly linked lists, dynamic allocation (`malloc`, `free`), string hashing, case-insensitive comparison, error handling with cleanup on partial failure, empirical performance profiling.

---

## Reflections

Week 5 turned memory from something observed into something managed. Inheritance introduced the foundation at small scale: a recursive tree of heap-allocated structs, where the base case, the pointer wiring, and the order of deallocation all have to be right, including on the failure path. Speller carried the same discipline to a structure holding the entire dictionary, where every node is allocated in `load`, traversed in `check`, and released in `unload`. It also made the cost of design decisions measurable: `check` runs once for every word in the text, so the hash function and bucket count show up directly in the timing output. The central lesson was that a data structure is chosen for what it costs, in time and memory, to use.
