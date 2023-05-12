def main():
    text = input("Text: ")

    letters_counter = count_letters(text)
    words_counter = count_words(text)
    sentences_counter = count_sentences(text)

    # Calculate average letters and sentences by diving both with words_counter and multiplying by 100
    average_letters = letters_counter / words_counter * 100
    average_sentences = sentences_counter / words_counter * 100

    # Calculate liauIndex, while making sure to round the result to the nearest integer
    liau_index = round(0.0588 * average_letters - 0.296 * average_sentences - 15.8)

    # Output result accordingly
    if liau_index < 1:
        print("Before Grade 1")

    elif liau_index > 16:
        print("Grade 16+")

    else:
        print(f"Grade {liau_index}")


# Get total number of letters using isalpha method
def count_letters(text):
    counter = 0

    for word in text:

        if word.isalpha():
            counter += 1

    return counter


# Get total number of words using isspace method
def count_words(text):
    counter = 1

    for word in text:

        if word.isspace():
            counter += 1

    return counter


# Get total number of sentences by checking if a letter is a dot, esclamation mark, or question mark
def count_sentences(text):
    counter = 0

    for word in text:

        # Source code for getting ASCII value of a word: https://www.delftstack.com/howto/python/convert-string-to-ascii-python/
        word_to_int = ord(word)

        if word_to_int == 46 or word_to_int == 33 or word_to_int == 63:
            counter += 1

    return counter


main()
