// Dziugas Mikalkenas
// 29 March 2019
// Problem Set 2

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int isInputAlpha(string prompt);
int shift(char c);
void printCiphered(unsigned char ciphered_char, int higherThan);

int main(int argc, string argv[])
{
    if (argc == 2)
    {        
        isInputAlpha(argv[1]);        
        string plaintext = get_string("plaintext: ");

        int plaintextLength = strlen(plaintext);
        int keywordLength = strlen(argv[1]);
        
        if (plaintextLength == 0)
        {
            printf("Please specify plaintext\n");
            return 1;
        }

        int i = 0;
        int j = 0;
        
        printf("ciphertext: ");
        
        while (i < keywordLength)
        {
            int key = shift(argv[1][i]);
            //printf("current key: %i\n", key);
            while (j < plaintextLength)
            {
                if (isalpha(plaintext[j]))
                {
                    //printf("plainchar: %i \n", plaintext[j]);
                    unsigned char ciphered_char = plaintext[j] + key % 26;
                    //printf("cipherchar: %i \n", ciphered_char);
                    if (islower(plaintext[j]))
                    {
                        printCiphered(ciphered_char,122);
                    }
                    else if (isupper(plaintext[j]))
                    {
                        printCiphered(ciphered_char,90);
                    }
                    i++;
                    j++;
                    break;
                }
                else
                {
                    printf("%c", plaintext[j]);
                    j++;
                }               
            }
            if (i == keywordLength)
            {
                i = 0;
            }
            if (j == plaintextLength)
            {
                break;
            }
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./vigenere <keyword>\n");
        return 1;
    }
}

int isInputAlpha(string prompt)
{
    int stringLength = strlen(prompt);
    for (int i = 0; i < stringLength; i++)
    {
        if (!isalpha(prompt[i]))
        {
            printf("Usage: ./vigenere <keyword>\n");
            exit(1);
        }
    }
    return atoi(prompt);
}

int shift(char c)
{
    if (isupper(c))
    {
        return c - 65;
    }
    else if (islower(c))
    {
        return c - 97;
    }
    else
    {
        exit(1);
    }
}

void printCiphered(unsigned char ciphered_char, int higherThan)
{
    if (ciphered_char > higherThan)
    {
        printf("%c", ciphered_char - 26);
        //printf("%i\n", ciphered_char - 26);
    }
    else
    {
        printf("%c", ciphered_char);
        //printf("%i\n", ciphered_char);                          
    } 
}
