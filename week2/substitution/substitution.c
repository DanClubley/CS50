
// CS50 Week 2 - Arrays : Substitution
// Dan Clubley 22 Feb 2023
// Uses a substitution cypher to encrypt text
// The cypher is passed as a command line argument and must contain one one of each character, returns error message if not
// Once executed, prompts user for text to encrypt and returns encrypted text

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int check_input(int n, string s);
char swap_char(char c, string s);

int main(int argc, string argv[])
{
    // Checks command line arguments
    int returnvalue = check_input(argc, argv[1]);

    // If comman line arguments incorrect return fault code
    if (returnvalue != 0)
    {
        return returnvalue;
    }

    string key = argv[1];

    // Get plaintext string
    string plaintext = get_string("plaintext:  ");
    string ciphertext = plaintext;

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
    // If more than one (or none) argument is passed
    if (n != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // If argument length is not 26 characters
    if (strlen(s) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // If non alphabetical argument is passed
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(s[i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    // Checks for one of each letter in the key
    int k;
    for (int i = 0; i < 26; i++)
    {
        k = 0;
        for (int j = 0; j < 26; j++)
        {
            if (s[j] == 65 + i || s[j] == 97 + i)
            {
                k++;
            }
        }
        if (k != 1)
        {
            printf("Key must contain one of each character.\n");
            return 1;
        }
    }

    return 0;
}

char swap_char(char c, string s)
{
    if (c >= 65 && c <= 90) //  Uppercase
    {
        // Set letter as number 0 - 25, replace from key
        return toupper(s[c - 65]);
    }
    else if (c >= 97 && c <= 122) // Lower case
    {
        // Set letter as number 0 - 25, replace from key
        return tolower(s[c - 97]);
    }
    else
    {
        return c;
    }
}
