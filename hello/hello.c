#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get name from user
    string name = get_string("What's your name?: ");

    // Print user name
    printf("hello, %s\n", name);
}