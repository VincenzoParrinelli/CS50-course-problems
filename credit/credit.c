#include <cs50.h>
#include <stdio.h>

int getLast2Digits(long cardNumber);
int getLastDigit(long cardNumber);

int main(void)
{
    // Initialize variables
    long cardNumber = get_long("Enter credit card number: ");

    // Get a copy of cardNumber so the algorithm can use this later to check for digits
    long cardNumberCopy = cardNumber;
    int lastDigit = 0;
    int evenDigitsSum = 0;
    int splittedDigit = 0;
    int evenDigitMultiplied = 0;
    int oddDigitsSum = 0;
    int last2Digits = 0;
    int i;

    for (i = 1; cardNumberCopy + 1 / 10 > 0; i++)
    {
        lastDigit = cardNumberCopy % 10;

        cardNumberCopy /= 10;

        // Multipy digits starting from the second one by 2
        if (i % 2 == 0)
        {
            evenDigitMultiplied = lastDigit * 2;

            // If multiplied digit results in a double digit, split and add into evenDigitsSum variable
            // example: 7 * 2 = 14, split the 14 into 1 + 4 = 5 and sum it into evenDigitsSum variable
            while (evenDigitMultiplied >= 10)
            {
                splittedDigit = evenDigitMultiplied % 10;
                evenDigitMultiplied /= 10;
                evenDigitsSum += splittedDigit;
            }

            evenDigitsSum += evenDigitMultiplied;
        }
        // Get the remaining digits and sum it into oddDigitsSum variable
        else
        {
            oddDigitsSum += lastDigit;
        }
    }

    // Decrement counter by i since it has been intialized as 1 in the previous for loop
    i--;

    // Check if the last digit of the sum of even and odd (position) numbers is 0
    if ((evenDigitsSum + oddDigitsSum) % 10 == 0)
    {
        if (i == 15)
        {
            last2Digits = getLast2Digits(cardNumber);

            if (last2Digits == 34 || last2Digits == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (i == 16)
        {
            // Get last 2 and last digit
            last2Digits = getLast2Digits(cardNumber);
            lastDigit = getLastDigit(cardNumber);

            // If last 2 digits are between 51 and 55 then it's a mastercard
            if (last2Digits >= 51 && last2Digits <= 55)
            {
                printf("MASTERCARD\n");
            }
            // If last digit is 4 then it's a visa
            else if (lastDigit == 4)
            {
                printf("VISA\n");
            }
            // else card is not valid
            else
            {
                printf("INVALID\n");
            }
        }
        else if (i == 13 && getLastDigit(cardNumber) == 4)
        {
            printf("VISA\n");
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

// Source code for finding first 2 digits of a number: https://stackoverflow.com/questions/52489462/how-to-find-first-two-digits-in-c
int getLast2Digits(long cardNumber)
{
    while (cardNumber >= 100)
    {
        cardNumber /= 10;
    }

    return cardNumber;
}

// Source code for finding first digit of a number: https://codeforwin.org/2015/06/how-to-find-first-and-last-digit-of-any-number.html
int getLastDigit(long cardNumber)
{
    while (cardNumber >= 10)
    {
        cardNumber /= 10;
    }

    return cardNumber;
}
