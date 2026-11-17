# A program that prompts the user for a credit card number and then
# reports (via print) whether it is a valid American Express, MasterCard, or Visa card number,
# exactly to the problem named Credit in pset1, but now in python.

from cs50 import get_int

# Get input from user
card_number = get_int("Number: ")

while card_number < 0:
    card_number = get_int("Number: ")

# Make a copy to work with
temp = card_number

# Initialize variables for Luhn's algorithm
sum = 0
count = 0

# Calculate and apply Luhn's agorithm
while temp > 0:
    digit = temp % 10
    temp //= 10
    count += 1

    if count % 2 == 0:
        digit *= 2

        if digit > 9:
            digit = (digit // 10) + (digit % 10)

    sum += digit

# Validation check on Luhn's checksum
if sum % 10 != 0:
    print("INVALID")

# Check for length and prefix for card type
else:
    temp = card_number
    while temp >= 100:
        temp //= 10

    if (count == 15 and (temp == 34 or temp == 37)):
        print("AMEX")

    elif (count == 16 and (temp >= 51 and temp <= 55)):
        print("MASTERCARD")

    elif ((count == 13 or count == 16) and (temp // 10 == 4)):
        print("VISA")

    else:
        print("INVALID")
