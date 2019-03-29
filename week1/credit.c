// Dziugas Mikalkenas
// 26 March 2019
// Problem Set 1

#include <cs50.h>
#include <stdio.h>
#include <math.h>

double get_first_digits(double n);
double check_length(double n, int power);
void check_issuer(double n, double card_number);
int is_card_valid(double card_number, int length);
    
int main(void)
{
    double card_number;
    card_number = get_long("Number: ");    
    double first_digits = get_first_digits(card_number);
    check_issuer(first_digits, card_number);
}

// Gets first two digits
double get_first_digits(double n)
{
    while (n > 100)
    {
        n /= 10;
    }     
    return n;
}

// Checks length of Card Number
double check_length(double n, int power)
{
    n /= pow(10, power);
    return n;
}

// Check issuer conditions
void check_issuer(double first_digits, double card_number)
{
    int t = floor(first_digits);
    
    if ((t == 34 || \
         t == 37) && \
        (check_length(card_number, 14) >= 1 && check_length(card_number, 14) < 10))
    {
        if (is_card_valid(card_number, 15) == 1)
        {
            printf("AMEX\n");  
        }
        else
        {
            printf("INVALID\n"); 
        }
    }
    else if ((t / 10 == 4) && \
             (check_length(card_number, 15) >= 1 && check_length(card_number, 15) < 10))
    {
        if (is_card_valid(card_number, 16) == 1)
        {
            printf("VISA\n");  
        }
        else
        {
            printf("INVALID\n"); 
        }
    }
    else if ((t == 51 || \
              t == 52 || \
              t == 53 || \
              t == 54 || \
              t == 55) && \
             ((check_length(card_number, 12) >= 1 && check_length(card_number, 12) < 10) || \
              (check_length(card_number, 13) >= 1 && check_length(card_number, 13) < 10) || \
              (check_length(card_number, 14) >= 1 && check_length(card_number, 14) < 10) || \
              (check_length(card_number, 15) >= 1 && check_length(card_number, 15) < 10)))
    {
        if (is_card_valid(card_number, 13) == 1 || \
            is_card_valid(card_number, 14) == 1 || \
            is_card_valid(card_number, 15) == 1 || \
            is_card_valid(card_number, 16) == 1)
        {
            printf("MASTERCARD\n");  
        }
        else
        {
            printf("INVALID\n"); 
        }
    }
    else
    {
        printf("INVALID\n");           
    }
}

// Checks Luhn's Algorithm
int is_card_valid(double card_number, int length)
{
    int card_odd_array[length];
    int multi_odd_array[length];
    int multi_digit_sum = 0;
        
    for (int i = 1; i <= length; i++)
    {
        double whole = floor(check_length(card_number, i)) * 10;
        double remainder = floor(check_length(card_number, i - 1)) - whole;
        card_odd_array[i - 1] = remainder;
            
        if (i % 2 == 0)
        {
            multi_odd_array[i - 1] = remainder * 2;
        }
        else
        {
            multi_odd_array[i - 1] = 0;
        }  
            
        if (multi_odd_array[i - 1] > 9)
        {
            int iwhole = multi_odd_array[i - 1] / 10;
            int iremainder = multi_odd_array[i - 1] - iwhole * 10;
            multi_digit_sum += iwhole + iremainder;
        }
        else
        {
            multi_digit_sum += multi_odd_array[i - 1];
        }
    }
        
    int sum = multi_digit_sum;
        
    for (int i = 1; i <= length; i++)
    {
        if (i % 2 == 1)
        {
            sum += card_odd_array[i - 1];
        }
    }

    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }    
}
