from cs50 import get_int
import re


def main():
    # Ask for user input
    card_no = get_int("Number: ")

    # Check if input is correct
    while True:
        if isinstance(abs(card_no), int):
            break

    # Check if card is valid
    isCardValid(card_no)

    # Check cards brand
    cardBrand(card_no)

    exit(0)


def isCardValid(number):
    sum = 0

    # Adds odd digits*2 to sum
    for i in range(len(str(number))+1):
        if i == 0:
            continue
        if i % 2 == 0:
            product = 2*int(str(number)[-i])
            if product >= 10:
                sum += int(str(product)[0])
                sum += int(str(product)[1])
            else:
                sum += product

    # Adds even digits to sum
    for i in range(len(str(number))+1):
        if i == 0:
            continue
        if i % 2 != 0:
            sum += int(str(number)[-i])

    # If sum ends with 0 returns true
    if sum % 10 != 0:
        print("INVALID")
        exit(0)


def cardBrand(number):
    number_length = len(str(number))

    if re.search(r'^3[47]', str(number)) and number_length == 15:
        print("AMEX")
    elif re.search(r'^5[1-5]', str(number)) and number_length == 16:
        print("MASTERCARD")
    elif re.search(r'^4', str(number)) and (number_length == 13 or number_length == 16):
        print("VISA")
    else:
        exit(1)

    exit(0)


if __name__ == "__main__":
    main()

