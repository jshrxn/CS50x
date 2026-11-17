# A program that simply recreates the half-pyramid using hashes(#) for blocks in the problem Mario(more) in pset 1.

from cs50 import get_int

# Get height from user
height = get_int("Height: ")

# Re-prompt if height is out of valid range
while (height < 1 or height > 8):
    height = get_int("Height: ")

# Loop through each row(bottom to top)
for x in range(height):

    # Left Panel: Leading spaces to indent
    for s in range(height - x - 1):
        print(" ", end="")

    # Left Panel: Hashes
    for h in range(x + 1):
        print("#", end="")

    # Gap between halves
    print("  ", end="")

    # Right Panel: Hashes
    for h in range(x + 1):
        print("#", end="")

    # Newline after each row
    print()
