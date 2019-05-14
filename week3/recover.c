// Dziugas Mikalkenas
// 14 May 2019
// Problem Set 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // checks if correct number of cli arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover <filename>\n");
        return 1;
    }

    // remembers input filename
    char *infile = argv[1];

    // reads input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Error %s: ", infile);
        perror("");
        return 2;
    }

    // block to be read parameters
    int blockSize = 512;
    int noOfBlocks = 1;
    unsigned char *buffer = (unsigned char *) malloc(blockSize);
    memset(buffer, 0, blockSize);

    int alreadyFoundJPEG = 0;
    int jpegNo = 0;
    char filename[10];
    FILE *img = NULL;

    // itterates through the input file
    while (1)
    {
        // reads block
        int readVal = fread(buffer, blockSize, noOfBlocks, inptr);

        // checks if EOF
        if (readVal < noOfBlocks)
        {
            printf("EOF reached\n");
            return 0;
        }

        // checks if JPEG start
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xff) == 0xe0)
        {
            // check if JPEG was previously found
            if (alreadyFoundJPEG == 1)
            {
                alreadyFoundJPEG = 0;
                fclose(img);
                jpegNo++;
            }

            sprintf(filename, "%03i.jpg", jpegNo);;
            printf("Found %s JPEG\n", filename);

            img = fopen(filename, "w");
            fwrite(buffer, blockSize, noOfBlocks, img);
            alreadyFoundJPEG = 1;

        }
        // if JPEG was previously found - continues writing
        else if (alreadyFoundJPEG == 1)
        {
            fwrite(buffer, blockSize, noOfBlocks, img);
        }
        else
        {
            printf("JPEG not found\n");
        }
    }

    fclose(inptr);
    return 0;
}
