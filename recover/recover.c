#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        printf("Usage: ./recover IMAGE \n");
        return 1;
    }

    // Open memory card
    FILE *card = fopen(argv[1], "r");

    // If file is not found return an error
    if (card == NULL)
    {
        return 1;
    }

    // Initialize vars
    BYTE Buffer[512];
    bool isFirstImageFound = false;
    char filename[8];
    int imagesCounter = 0;
    FILE *img = NULL;

    // Read through memory card and store temporaly data into a buffer
    while (fread(&Buffer, 512, 1, card) == 1)
    {
        // If new image has been found
        if (Buffer[0] == 0xff && Buffer[1] == 0xd8 && Buffer[2] == 0xff && (Buffer[3] & 0xf0) == 0xe0)
        {
            // If is the first image close previous image file
            if (isFirstImageFound)
            {
                fclose(img);
            }
            // else set isFirstImage to true
            else
            {
                isFirstImageFound = true;
            }

            // Create new jpeg filename
            sprintf(filename, "%03i.jpg", imagesCounter++);

            // Set image file to filename and write into it
            img = fopen(filename, "w");
            fwrite(&Buffer, 512, 1, img);
        }
        // If image file already exists write into it
        else if (img != NULL)
        {
            fwrite(&Buffer, 512, 1, img);
        }
    }

    // Close opened files
    fclose(card);
    fclose(img);
    return 0;
}