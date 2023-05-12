def main():

    card_number = input("Enter credit card number: ")

    # Substring in python source: https://www.freecodecamp.org/news/how-to-substring-a-string-in-python/

    first_set_of_numbers = card_number[-2::-2]
    sum = 0

    # Multiply by 2 every number in the first set
    for number in first_set_of_numbers:

        number = int(number) * 2

        # If number is greater than 9 (means it is a 2 digit number) sum every digit individually
        # else add number to the sum
        if number > 9:
            sum += int(str(number)[0:1])
            sum += int(str(number)[1:2])
        else:

            sum += number

    second_set_of_numbers = card_number[-1::-2]

    # Sum every number in the second set
    for number in second_set_of_numbers:

        sum += int(number)

    # If last digit of sum is 0 start checking for card's circuit accordingly else print INVALID
    if str(sum)[-1] == str(0):

        first_digit = int(card_number[0:1])
        first_two_digits = int(card_number[0:2])
        card_number_length = len(card_number)

        if card_number_length == 15 and first_two_digits == 34 or first_two_digits == 37:
            print("AMEX")

        elif card_number_length == 16 and first_two_digits >= 51 and first_two_digits <= 55:
            print("MASTERCARD")

        elif card_number_length == 13 or card_number_length == 16 and first_digit == 4:
            print("VISA")

        else:
            print("INVALID")

    else:
        print("INVALID")


main()
