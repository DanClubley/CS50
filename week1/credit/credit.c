
// CS50 Week 1 - C : Credit
// Dan Clubley 22 Feb 2023
// Prompts user for a card number, re-promts if not a positive integer
// Returns if card number is american express, mastercard, visa or invalid (other)
// Does not cover all cases

#include <cs50.h>
#include <math.h>
#include <stdio.h>

// Luhn's algorith to see if card number is valid
// Checksum: Multiply every other digit by 2 starting with second to last digit
// Checksum: Add all of the digits together from above
// Checksum: Add all the remaining card digits to the total
// Checksum: If the total's last digit is 0, the card is valid

// Additional checks for different card types
// American express: 15 digits, starts with 34 or 37
// Mastercard, 16 digits, starts with 51, 52, 53, 54 or 55
// Visa, 13 or 16 digits, starts with 4

// Link for testing card numbers
// https://developer.paypal.com/api/nvp-soap/payflow/payflow-pro/payflow-pro-testing/

int checkLength(long number);
long checkMultiple(long number);

int main(void)
{
    long cardNumber;
    int total = 0;
    int length;
    int digits;

    // Prompt for card number, reprompt if not a positive number (or if non-numeric)
    do
    {
        cardNumber = get_long("Card number: ");
    }
    while (cardNumber <= 0);

    // Check length of card
    length = checkLength(cardNumber);

    //  Get first two digits
    digits = cardNumber / pow(10, (length - 2));

    // Calculate card number total as per checksum rules
    while (cardNumber > 0)
    {
        total += cardNumber % 10;
        cardNumber /= 10;
        total += checkMultiple(cardNumber % 10);
        cardNumber /= 10;
    }

    // Check if card number number is valid with a last digit of 0
    if ((total % 10) != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        // Check if AMEX
        if (length == 15 && (digits == 34 || digits == 37))
        {
            printf("AMEX\n");
        }
        // Check if MASTERCARD
        else if (length == 16 && digits >= 51 && digits <= 55)
        {
            printf("MASTERCARD\n");
        }
        // Check if VISA
        else if ((length == 13 || length == 16) && (digits / 10) == 4)
        {
            printf("VISA\n");
        }
        // If none of the above set to invalid
        else
        {
            printf("INVALID\n");
        }
    }
}

// Calculate digit length
int checkLength(long number)
{
    int count = 0;
    while (number != 0)
    {
        number /= 10;
        count++;
    }
    return count;
}

// Multiply by two, add digits together if 10 or above
long checkMultiple(long number)
{
    if (number * 2 >= 10)
    {
        number *= 2;
        return (number % 10) + number / 10;
    }
    else
    {
        return number * 2;
    }
}