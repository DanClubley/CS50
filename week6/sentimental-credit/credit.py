
# CS50 Week 5 - Python : Credit
# Dan Clubley 22 Feb 2023
# Checks credit card number, same as Week 1

# American express: 15 digits, starts with 34 or 37
# Mastercard, 16 digits, starts with 51, 52, 53, 54 or 55
# Visa, 13 or 16 digits, starts with 4

# Checksum: Multiply every other digit by 2 starting with second to last digit
# Checksum: Add all of the digits together from above
# Checksum: Add all the remaining card digits to the total
# Checksum: If the total's last digit is 0, the card is valid


def main():

    number = get_number()

    if check_sum(number):
        check_number(number)


def get_number():

    try:
        number = int(input("Number: "))
    except ValueError:
        print("INVALID")
        exit()cd

    return number


def check_sum(number):

    total = 0

    while number > 0:
        total += number % 10
        number = number // 10
        total += check_multiple(number % 10)
        number = number // 10

    if (total % 10) != 0:
        print("Total: " + str(total))
        print("INVALID")
        return False

    return True


def check_multiple(number):

    if number * 2 >= 10:
        number *= 2
        return (number % 10) + number // 10
    else:
        return number * 2


def check_number(number):

    s_number = str(number)

    if len(s_number) == 15 and int(s_number[:2]) in [34, 37]:
        print("AMEX")

    elif len(s_number) == 16 and int(s_number[:2]) in [51, 52, 53, 54, 55]:
        print("MASTERCARD")

    elif len(s_number) in [13, 16] and int(s_number[:1]) == 4:
        print("VISA")

    else:
        print("INVALID")


main()