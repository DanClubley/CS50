
// CS50 Week 2 - Arrays : Readability
// Dan Clubley 22 Feb 2023
// Prompts user for some text, returns the reading level according to Coleman-Liau index

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Use Coleman-Liau index to calculate US reading level
// index = 0.0588 * L - 0.296 * S - 15.8
// L = average number of letters per 100 words of text
// L = (number of letters / number of words) * 100
// S = average number of sentences per 100 words of text
// S = (number of sentences / number of words) * 100

// Use get_string to prompt the user for a string

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_index();

int letters, words, sentences, length;
int value = 0;

int main(void)
{
    string text = get_string("Text: ");
    // printf("Text: %s\n", text);

    length = strlen(text);
    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);

    value = calculate_index(letters, words, sentences);

    // printf("Letters   = %i\n", letters);
    // printf("Words     = %i\n", words);
    // printf("Sentences = %i\n", sentences);
    // printf("Index     = %i\n", value);

    if (value < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (value >= 1 && value < 16)
    {
        printf("Grade %i\n", value);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string text)
{
    // Count all alphabetical characters
    int n = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            n++;
        }
    }
    return n;
}

int count_words(string text)
{
    // Counts all spaces + 1 for word count
    int n = 1;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == 32)
        {
            n++;
        }
    }
    return n;
}

int count_sentences(string text)
{
    // Counts all . ! ?
    int n = 0;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            n++;
        }
    }
    return n;
}

int calculate_index()
{
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;

    return round((0.0588 * L) - (0.296 * S) - 15.8);
}