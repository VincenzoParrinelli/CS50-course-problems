import csv
import sys


def main():

    # Check for command-line usage

    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database file into a variable

    data_filename = sys.argv[1]
    persons_data = []

    with open(data_filename) as file:
        reader = csv.DictReader(file)

        for person_data in reader:
            persons_data.append(person_data)

    # Read DNA sequence file into a variable
    sequence_filename = sys.argv[2]
    dna_sequence = ""

    with open(sequence_filename) as file:
        dna_sequence = file.read()

    # Find longest match of each STR in DNA sequence
    subsequences = []
    str_longest_matches = {}

    # How to get every keys in a dict except for the first one + error fix
    # Source: https://bobbyhadz.com/blog/python-dict-keys-object-is-not-subscriptable
    for person in persons_data:
        subsequences = list(person.keys())[1:]

    for subsequence in subsequences:
        str_longest_matches[subsequence] = longest_match(dna_sequence, subsequence)

    # Check database for matching profiles

    for person in persons_data:
        count = 0

        for subsequence in subsequences:
            if int(person[subsequence]) == str_longest_matches[subsequence]:
                count += 1

        if count == len(subsequences):

            print(person["name"])

            return

    print("No match")

    return


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


main()
