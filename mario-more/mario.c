#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;

    // Get height from user, prompt again if height is less than, equal to 0 or higher than 8
    do
    {
        height = get_int("Enter height: ");
    }

    while (height <= 0 || height > 8);

    // for loop for printing pyramid
    for (int i = 0; i < height; i++)
    {
        printf("\n");

        // Print left side pyramid
        for (int j = 0; j < height; j++)
        {
            // Add a space if j (current row) is lower than height - 1
            // else add an hash
            if (i + j < height - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }

        // Add 2 spaces gap between the 2 sides
        printf("  ");

        // Print right side pyramid
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
    }

    printf("\n");
}