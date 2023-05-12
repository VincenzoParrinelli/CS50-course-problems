#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "wav.h"

bool check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc < 2)
    {
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        return 1;
    }

    // Read header into an array
    WAVHEADER header;
    fread(&header, 44, 1, input);

    // Use check_format to ensure WAV format
    check_format(header);

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");

    if (output == NULL)
    {
        return 1;
    }

    // Write header to file
    fwrite(&header, 44, 1, output);

    // Use get_block_size to calculate size of block
    int blockSize = get_block_size(header);

    // Write reversed audio to file
    BYTE Buffer[512];
    fseek(input, 0, SEEK_END);

    while (ftell(input) >= 44)
    {
        printf("%ld\n", ftell(input));

        fread(&Buffer, blockSize, 1, input);

        fwrite(&Buffer, blockSize, 1, output);

        fseek(input, -(blockSize * 2), SEEK_CUR);
    }

    fclose(input);
    fclose(output);
    return 0;
}

bool check_format(WAVHEADER header)
{

    if (header.format[0] == 87 && header.format[1] == 65 && header.format[2] == 86 && header.format[3] == 69)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int get_block_size(WAVHEADER header)
{
    int bytesPerSample = header.bitsPerSample / 8;

    return bytesPerSample * header.numChannels;
}