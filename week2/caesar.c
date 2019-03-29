// Dziugas Mikalkenas
// 28 March 2019
// Problem Set 2

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int isInputValid(string prompt);

int main(int argc, string argv[])
{
    if (argc == 2)
    {        
        int key = isInputValid(argv[1]);        
        string plaintext = get_string("plaintext: ");
        int plaintextLength = strlen(plaintext);
        unsigned char ciphertext[plaintextLength];
        
        for (int i = 0; i < plaintextLength; i++)
        {
            if (isalpha(plaintext[i]))
            {
                if (islower(plaintext[i]))
                {
                    ciphertext[i] = plaintext[i] + key % 26;
                    if (ciphertext[i] > 122)
                    {
                        ciphertext[i] -= 26;
                    }
                }
                else if (isupper(plaintext[i]))
                {
                    ciphertext[i] = plaintext[i] + key % 26;
                    if (ciphertext[i] > 90)
                    {
                        ciphertext[i] -= 26;
                    }
                }
            }
            else
            {
                ciphertext[i] = plaintext[i];
            }   
        }
        printf("ciphertext: %s\n", ciphertext);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

int isInputValid(string prompt)
{
    int stringLength = strlen(prompt);
    for (int i = 0; i < stringLength; i++)
    {
        if (!isdigit(prompt[i]))
        {
            printf("Usage: ./caesar key\n");
            exit(1);
        }
    }
    return atoi(prompt);
}
