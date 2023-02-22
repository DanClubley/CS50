
# CS50 Week 5 - Python : DNA
# Dan Clubley 22 Feb 2023
# Checks for consecutive strings of DNA in CSV file to match DNA to person

import csv
import sys

def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("USAGE: python dna.py database.csv sequence.txt")
        exit(1)

    # Read database file into a variable
    with open(sys.argv[1]) as csv_file:
        reader = csv.DictReader(csv_file)
        database = list(reader)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as txt_file:
        sequence = txt_file.read()

    # Find longest match of each STR in DNA sequence
    str_list = list(database[0].keys())[1:]
    counts = {}
    for value in str_list:
        counts[value] = longest_match(sequence, value)

    # Check database for matching profiles
    for row in database:
        checks = 0
        for value in str_list:
            if int(row[value]) == counts[value]:
                checks += 1
                if checks == len(str_list):
                    print(row["name"])
                    exit(0)

    print("No match")
    exit(0)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()