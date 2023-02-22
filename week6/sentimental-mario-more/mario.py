
# CS50 Week 5 - Python : Mario
# Dan Clubley 22 Feb 2023
# Prompts for height, returns Mario pyramid of height

def main():

    height = get_height()

    for i in range(height):
        add_line(i + 1, height)


def get_height():

    while True:

        try:
            n = int(input("Height: "))
        except ValueError:
            n = 0

        if n >= 1 and n <= 8:
            break

    return n


def add_line(n, height):

    print(" " * (height - n), end="")
    print("#" * n + "  " + "#" * n)


main()