#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Initialize integers
    int starting_size = 0;
    int ending_size = 0;
    int new_lamas = 0;
    int passed_lamas = 0;

    int years = 0;

    // Get starting size from user as long as the user inputs a value less than 9
    do
    {
        starting_size = get_int("Enter a starting size: ");
    }

    while (starting_size < 9);

    // Get ending size from user as long as the user inputs a value less than the starting size
    do
    {
        ending_size = get_int("Enter an ending size: ");
    }

    while (ending_size < starting_size);

    // Add 1 to years counter as long as starting size is less than ending size
    while (starting_size < ending_size)
    {
        new_lamas = starting_size / 3;
        passed_lamas = starting_size / 4;

        starting_size += new_lamas - passed_lamas;

        years++;
    }

    printf("Years: %i\n", years);
}
