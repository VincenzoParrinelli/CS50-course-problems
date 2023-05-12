from cs50 import get_int


def main():

    # Get height from user, prompt again if height is less than, equal to 0 or higher than
    while True:
        height = get_int("Enter height: ")

        if height > 0 and height <= 8:
            break

    # for loop for printing pyramid
    for i in range(height):
        print("")

    # Print left side pyramid
        for j in range(height):

            # Add a space if j (current row) is lower than height - 1
            # else add an hash
            if i + j < height - 1:
                print(" ", end="")
            else:
                print("#", end="")

        # Add 2 spaces gap between the 2 sides
        print("  ",  end="")

        # Print right side pyramid
        for j in range(i + 1):

            print("#", end="")

    print("")


main()
