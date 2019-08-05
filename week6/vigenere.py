import sys
import string
from cs50 import get_string

# Checks for corrent number of arguments
if len(sys.argv) != 2:
    print("Usage: python vigenere.py <keyword>")
    exit(1)

# Checks if keyword is alphabetic
if not sys.argv[1].isalpha():
    print("Usage: python vigenere.py <keyword>")
    exit(1)

k = sys.argv[1].lower()
keywordLength = len(k)
p = get_string("plaintext: ")
plaintextLength = len(p)

ciphertext = ""

i = 0
j = 0

# Enciphers
while i < keywordLength:
    while j < plaintextLength:
        if p[j] in string.ascii_uppercase:
            ciphered_char = ((string.ascii_uppercase.index(p[j]) + string.ascii_lowercase.index(k[i])) % 26) + 65
            ciphertext += chr(ciphered_char)
            i += 1
            j += 1
        elif p[j] in string.ascii_lowercase:
            ciphered_char = ((string.ascii_lowercase.index(p[j]) + string.ascii_lowercase.index(k[i])) % 26) + 97
            ciphertext += chr(ciphered_char)
            i += 1
            j += 1
        else:
            ciphertext += p[j]
            j += 1

        if i == keywordLength:
            i = 0
    if j == plaintextLength:
        break

print(f'ciphertext: {ciphertext}') 
