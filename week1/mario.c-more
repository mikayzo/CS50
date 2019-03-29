// Dziugas Mikalkenas
// 26 March 2019
// Problem Set 1
 
#include <cs50.h>
#include <stdio.h>

void whitespaces(int i, int height);
void hashes(int i);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);
    
    for (int i = 1; i <= height; i++)
    {     
        whitespaces(i,height);
        hashes(i);
        printf("  ");
        hashes(i);
        printf("\n");
    }
}

// Print number of whitespaces
void whitespaces(int i, int height)
{
    int no_whitespaces = height - i;
    while (no_whitespaces > 0)
    {
        printf(" ");
        no_whitespaces--;
    }
}

// Print number of hashes
void hashes(int i)
{
    while (i > 0) 
    {
        printf("#");
        i--;
    }  
}
