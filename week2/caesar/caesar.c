
// CS50 Week 2 - Arrays : Caesar
// Dan Clubley 22 Feb 2023
// Encrypts text using Caesar's cypher (increments each letter by key value, if key is 1: A becomes B, B becomes C, Z becomes A, etc.)
// Pass key as command line argument, return error statement if not an integer
// Once executed, prompts user for text to encrypt and returns encrypted text

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int check_input(int n, string s);
char swap_char(char c, int n);

int key;

int main(int argc, string argv[])
{
    string plaintext;
    string ciphertext;

    // Checks command line arguments
    int returnvalue = check_input(argc, argv[1]);

    // If command line arguments incorrect return fault code
    if (returnvalue != 0)
    {
        printf("Usage: ./caesar key\n");
        return returnvalue;
    }

    // Get plaintext string
    plaintext = get_string("plaintext: ");
    ciphertext = plaintext;

    // Check each character in string
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // If character is alphabetical, swap character with key
        if (isalpha(plaintext[i]))
        {
            ciphertext[i] = swap_char(plaintext[i], key);
        }
    }

    printf("ciphertext: %s\n", ciphertext);
    return 0;
}


int check_input(int n, string s)
{
    // If more than one argument is passed
    if (n != 2)
    {
        return 1;
    }

    // If non numeric argument is passed
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        if (!isdigit(s[i]))
        {
            return 1;
        }
    }

    // Convert argument from string to integer
    key = atoi(s);

    // If argument is a negative number
    if (key < 0)
    {
        return 1;
    }

    // Return 0 if passed all checks
    return 0;
}


char swap_char(char c, int n)
{
    if (c >= 65 && c <= 90) //  Uppercase
    {
        // Set letter as number 0 - 25, add the key and set as remainder of 26. Set back to uppercase ASCII #
        return (c - 65 + n) % 26 + 65;
    }
    else if (c >= 97 && c <= 122) // Lower case
    {
        // Set letter as number 0 - 25, add the key and set as remainder of 26. Set back to lowercase ASCII #
        return (c - 97 + n) % 26 + 97;
    }
    else
    {
        return c;
    }
}

