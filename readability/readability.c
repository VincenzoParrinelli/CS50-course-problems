#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Get input from user
    string text = get_string("Text: ");

    // Get counters accordingly
    int lettersCounter = count_letters(text);
    int wordsCounter = count_words(text);
    int sentencesCounter = count_sentences(text);

    // Initialize vars
    float averageLetters = 0;
    float averageSentences = 0;
    int liauIndex = 0;

    // Calculate average letters and sentences by converting letters to a float, in the end
    // divide letters and words and multiply them by 100
    averageLetters = (float)lettersCounter / wordsCounter * 100;
    averageSentences = (float)sentencesCounter / wordsCounter * 100;

    // Calculate liauIndex, make sure to round the result to the nearest integer
    liauIndex = round(0.0588 * averageLetters - 0.296 * averageSentences - 15.8);

    // Output result accordingly
    if (liauIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (liauIndex > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", liauIndex);
    }
}

// Get total number of letters using isalpha method
int count_letters(string text)
{
    int counter = 0;

    for (int i = 0; i < strlen(text); i++)
    {

        if (isalpha(text[i]))
        {
            counter++;
        }
    }

    return counter;
}

// Get total number of word using isspace method
int count_words(string text)
{
    int counter = 1;

    for (int i = 0; i < strlen(text); i++)
    {

        if (isspace(text[i]))
        {
            counter++;
        }
    }

    return counter;
}

// Get total number of sentences by checking if a letter is a dot, esclamation mark, or question mark
int count_sentences(string text)
{
    int counter = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        int textToInt = (int)text[i];

        if (textToInt == 46 || textToInt == 33 || textToInt == 63)
        {
            counter++;
        }
    }

    return counter;
}