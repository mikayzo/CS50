// Dziugas Mikalkenas
// 5 April 2019
// Problem Set 2

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

string get_salt(string hash);
void check_hash(char *pa, string salt, string hash, float begin);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("usage: ./crack <hash>\n");
        return 1;
    }

    else
    {
        // get salt
        string salt = get_salt(argv[1]);
        char a[6] = "";
        char *pa = a;

        clock_t begin = clock();
        
        // 1 char
        for (int i = 65; i <= 122; i++)
        {
            pa[0] = i;
            check_hash(pa, salt, argv[1], begin);
        }
        
        // 2 chars
        for (int i = 65; i <= 122; i++)
        {
            for (int j = 65; j <= 122; j++)
            {
                pa[0] = i;
                pa[1] = j;
                check_hash(pa, salt, argv[1], begin);
            }
        }
        
        // 3 chars
        for (int i = 65; i <= 122; i++)
        {
            for (int j = 65; j <= 122; j++)
            {
                for (int k = 65; k <= 122; k++)
                {
                    pa[0] = i;
                    pa[1] = j;
                    pa[2] = k;
                    check_hash(pa, salt, argv[1], begin);
                }
            }
        }  
        
        // 4 chars
        for (int i = 65; i <= 122; i++)
        {
            for (int j = 65; j <= 122; j++)
            {
                for (int k = 65; k <= 122; k++)
                {
                    for (int l = 65; l <= 122; l++)
                    {
                        pa[0] = i;
                        pa[1] = j;
                        pa[2] = k;
                        pa[3] = l;
                        check_hash(pa, salt, argv[1], begin);
                    }
                }
            }
        }   
        
        // 5 chars
        for (int i = 65; i <= 122; i++)
        {
            for (int j = 65; j <= 122; j++)
            {
                for (int k = 65; k <= 122; k++)
                {
                    for (int l = 65; l <= 122; l++)
                    {
                        for (int m = 65; m <= 122; m++)
                        {
                            pa[0] = i;
                            pa[1] = j;
                            pa[2] = k;
                            pa[3] = l;
                            pa[4] = m;
                            check_hash(pa, salt, argv[1], begin);
                        }
                    }
                }
            }
        } 
        printf("Unable to break\n");
    }
}

string get_salt(string hash)
{
    char *salt;
    salt = (char *)malloc(3);
    
    int i = 0;
    while (i < 2)
    {
        salt[i] = hash[i];
        i++;
    }
    return salt;
}

void check_hash(char *pa, string salt, string hash, float begin)
{
    string encrypted = crypt(pa, salt);
    if (strcmp(encrypted, hash) == 0)
    {
        printf("%s\n", pa);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Time spent: %fs\n", time_spent);
        exit(0);
    }
}
