# Week 4 — Memory

Low-level data representation and manipulation: binary file I/O, fixed-width integer types, and treating images and storage media as raw byte streams.

---

## Volume

A program that modifies the amplitude of a WAV audio file by a user-specified scaling factor. A WAV file consists of a 44-byte header followed by a sequence of 16-bit signed samples. The header is copied verbatim to the output, and each sample is read, multiplied by the factor, and written back, preserving the file's format while altering its amplitude.

**Concepts:** binary file I/O (`fopen`, `fread`, `fwrite`), fixed-width integer types (`uint8_t`, `int16_t`), file formats as structured byte layouts.

---

## Filter (More)

A BMP image processor implementing four filters over an in-memory 2D array of `RGBTRIPLE` structs, one per pixel:

- **Grayscale:** averages each pixel's red, green, and blue channels to produce a uniform gray value.
- **Reflection:** mirrors the image horizontally by swapping pixels across the vertical axis.
- **Blur:** a box blur that replaces each pixel with the mean of its 3x3 neighborhood, with explicit handling of edge and corner pixels where the neighborhood is truncated.
- **Edges:** Sobel edge detection. Each pixel is convolved with the Gx and Gy kernels, the two gradients are combined as √(Gx² + Gy²), and the result is capped at 255. Out-of-bounds neighbors are treated as black.

Blur and edges read from an unmodified copy of the image, so that already-processed pixels never contaminate the neighborhood calculations of their neighbors. Each channel is explicitly rounded and clamped to remain a valid 8-bit value.

**Concepts:** 2D arrays of structs, convolution kernels, boundary-condition handling, preserving source data during in-place transformations, integer overflow and saturation.

---

## Recover

A forensic recovery tool that reconstructs JPEG files from a raw memory-card image. The program reads the card in 512-byte blocks and scans for the JPEG signature at the start of each block (`0xff 0xd8 0xff`, with the fourth byte in the range `0xe0`–`0xef`). Each signature closes the current output file, if any, and opens a new sequentially named one (`000.jpg`, `001.jpg`, ...), and subsequent blocks are appended until the next signature or the end of the card.

**Concepts:** block-oriented I/O, file signature detection, bitwise masking, file handle lifecycle management, formatted filename generation with `sprintf`.

---

## Reflections

Week 4 exposed the representation beneath the abstractions: audio as a stream of integers, images as 2D arrays of pixel structs, and storage as a sequence of fixed-size blocks. Filter (More) was a deliberate stretch over the Less variant, since Sobel edge detection draws on every skill from the week at once: boundary logic, working from a copy of the source data, and numeric clamping. Recover then inverted the problem, reconstructing files from raw bytes with no filesystem metadata to guide it. Across all three, the central discipline was precision: the correct type, the correct size, the correct boundary, and an exact accounting of every byte read and written.
