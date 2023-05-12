#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{

    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int score = 0;
    int wordToInt = 0;
    int pointsIndex = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        // Reset pointsIndex for each iteration
        pointsIndex = 0;

        // Convert string to int
        wordToInt = (int)tolower(word[i]);

        if (wordToInt >= 97 && wordToInt <= 122)
        {
            // Remove alphabet's length from converted int
            wordToInt -= 26;

            // Get last value of number, this will resemble alphabet's index
            pointsIndex = wordToInt % 10;

            // Add 20 or 10 to pointsIndex accordingly ensuring a correct convertion from ASCII to alphabet's letter position
            if (wordToInt >= 90)
            {
                pointsIndex += 20;
            }
            else if (wordToInt >= 80)
            {
                pointsIndex += 10;
            }

            score += POINTS[pointsIndex - 1];
        }
    }

    return score;
}
