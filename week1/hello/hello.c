
// CS50 Week 1 - C : Hello
// Dan Clubley 22 Feb 2023
// Prompts user for name, returns with "Hello, name"

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string answer = get_string("What's your name? ");
    printf("Hello, %s\n", answer);
}