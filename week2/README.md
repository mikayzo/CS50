## caesar.c:

    Usage: ./caesar <key>
    
    Asks user for a key (digit) and a plaintext. Then enciphers the plaintext with caesar cipher and return ciphertext.

## vigenere.c:

    Usage: ./vigenere <keyword>

    Asks user for a keyword and a plaintext. Then enciphers the plaintext with vigenere cipher and returns ciphertext.

## crack.c:
    
    Usage: ./crack <hash>

    Asks user to input a <hash>, then deciphers it by using crypt(pa, salt) function. Salt is the first two characters of <hash>.
