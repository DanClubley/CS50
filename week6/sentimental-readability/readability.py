
# CS50 Week 5 - Python : Readability
# Dan Clubley 22 Feb 2023
# Checks coleman-liau index for text, same as Week 1


# Use Coleman-Liau index to calculate reading level
# index = 0.0588 * L - 0.296 * S - 15.8
# L = average number of letters per 100 words of text
# L = (number of letters / number of words) * 100
# S = average number of sentences per 100 words of text
# S = (number of sentences / number of words) * 100


def main():

    text = get_string()

    letters = sum(i.isalpha() for i in text)
    words = len(text.split())
    sentences = sum(i in [".", "!", "?"] for i in text)

    index = calculate_index(letters, words, sentences)

    if index < 1:
        print("Before Grade 1")

    elif index >= 1 and index < 16:
        print("Grade " + str(index))

    else:
        print("Grade 16+")


def get_string():

    string = (input("String: "))
    return string


def calculate_index(letters, words, sentences):

    L = letters / words * 100
    S = sentences / words * 100

    return round((0.0588 * L) - (0.296 * S) - 15.8)


main()
