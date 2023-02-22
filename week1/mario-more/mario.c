
// CS50 Week 1 - C : Mario
// Dan Clubley 22 Feb 2023
// Prompts user for a height, re-prompts if value is not an int between 1 and 8
// Builds a pyramid of #s to the height specified

#include <stdio.h>
#include <cs50.h>

int height;

void addLine(int n);

int main(void)
{
    do
    {
        height = get_int("Height: ");
    }
    // Go back to the do loop if height is less than 1 or greater than 8
    while (height < 1 || height > 8);

    // Run AddLine function for lines 1 - height
    int h;
    for (h = 0; h < height; h++)
    {
        addLine(h + 1);
    }
}

void addLine(int n)
{
    int i;
    // Set the initial spacing
    for (i = 0; i < height - n; i++)
    {
        printf(" ");
    }
    // Add hashes
    for (i = 0; i < n; i++)
    {
        printf("#");
    }
    // Add centre spacing
    printf("  ");
    // Add ending hashes
    for (i = 0; i < n; i++)
    {
        printf("#");
    }
    // Set to new line
    printf("\n");
}


