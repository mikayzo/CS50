#!/usr/bin/env python3

from cs50 import get_string
from sys import argv


def main():

    if len(argv) != 2:
        print("Usage: python3 bleep.py dictionary")
        exit(1)

    banned_words = []

    try:
        with open(argv[1]) as f:
            for line in f:
                banned_words.append(line.strip())
    except FileNotFoundError:
        print(f"ERROR: File '{argv[1]}' Not Found")
        exit(1)

    check_line = input("What message would you like to censor?\n") 

    filtered = []

    for word in check_line.split():
        if word.lower() in banned_words:
            filtered.append("*" * len(word))
        else:
            filtered.append(word)

    censored_line = ' '.join(filtered)

    print(censored_line)


if __name__ == "__main__":
    main()
