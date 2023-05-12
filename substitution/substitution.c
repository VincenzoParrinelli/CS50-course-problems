#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string key = argv[1];

    // Check if command-line arguments are valid
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Loop through the string and check for non alphabetic characters, if one is found return with an error
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        // Loop for the string for each character and if there is a duplicate return with an error
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    // Get plaintext from user and initialize vars
    string plainText = get_string("plaintext: ");
    int wordToInt = 0;
    int keyIndex = 0;

    printf("ciphertext: ");

    for (int i = 0; i < strlen(plainText); i++)
    {
        // Check if char plaintext string is alphabetic
        if (isalpha(plainText[i]))
        {
            // Set wordToInt to the current char's ASCII converted to an integer
            wordToInt = (int)tolower(plainText[i]);

            // Subtract alphabet's length
            wordToInt -= 26;

            // Get last value
            keyIndex = wordToInt % 10;

            // Add +20 or +10 accordingly based on alphabet's and ASCII length
            // ASCII values of lowercase letters range from 97 to 122, if the ASCII value is less than 106, remove the alphabet's length
            // and get the last value it would be equal to the corresponding english alphabet's letter position.
            // If the ASCII value is greater than 106 add 10 to keyIndex, if it is greater than 90 add 20 to keyIndex

            if (wordToInt >= 90)
            {
                keyIndex += 20;
            }
            else if (wordToInt >= 80)
            {
                keyIndex += 10;
            }

            // These if checks ensure that letters cases remain equal 
            if (islower(plainText[i]))
            {
                printf("%c", tolower(key[keyIndex - 1]));
            }
            else
            {
                printf("%c", toupper(key[keyIndex - 1]));
            }
        }
        else
        {
            printf("%c", (plainText[i]));
        }
    }

    printf("\n");

    return 0;
}