// Dziugas Mikalkenas
// 13 May 2019
// Problem Set 3

// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int isdigit(char *a);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy scale infile outfile\n");
        return 1;
    }

    // check if scale is valid
    if (isdigit(argv[1]) != 0)
    {
        return 2;
    }

    // remember scale
    float scale = atof(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w+");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    if (scale == 1)
    {
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

        int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            for (int j = 0; j < bi.biWidth; j++)
            {
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            fseek(inptr, padding, SEEK_CUR);

            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }

        fclose(inptr);
        fclose(outptr);
        return 0;
    }
    else if (scale > 1)
    {
        int in_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        int biWidthOrig = bi.biWidth;
        int biHeightOrig = abs(bi.biHeight);

        bi.biWidth *= scale;
        bi.biHeight *= scale;

        int out_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        printf("in_padding %d\n", in_padding);
        printf("out_padding %d\n", out_padding);

        bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + out_padding) * abs(bi.biHeight);
        bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

        // itterates vertically
        for (int i = 0; i < biHeightOrig; i++)
        {
            fpos_t CURSOR;
            // saves starting line cursor
            fgetpos(inptr, &CURSOR);

            // scales vertically
            for (int sc_h = 0; sc_h < scale; sc_h++)
            {
                // iterates horizontally
                for (int j = 0; j < biWidthOrig; j++)
                {
                    RGBTRIPLE triple;
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    // scales horizontally
                    for (int sc_w = 0; sc_w < scale; sc_w++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
                // skips over padding
                fseek(inptr, in_padding, SEEK_CUR);
                // writes padding
                for (int k = 0; k < out_padding; k++)
                {
                    fputc(0x00, outptr);
                }

                // check if scaled enough and skips reseting cursor
                if (sc_h + 1 == scale)
                {
                    break;
                }
                // resets cursor to line start if hasnt scalled horizontaly yet
                fsetpos(inptr, &CURSOR);
            }
        }
        fclose(inptr);
        fclose(outptr);
        return 0;
    }
    else if ((scale < 1) && (fmod(bi.biWidth, scale) == 0.0) && (fmod(bi.biHeight, scale) == 0.0))
    {

        int in_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        int biWidthOrig = bi.biWidth;
        int biHeightOrig = abs(bi.biHeight);

        bi.biWidth *= scale;
        bi.biHeight *= scale;

        int out_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        printf("Out padding %d\n", out_padding);

        bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + out_padding) * abs(bi.biHeight);
        bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


        printf("Original biWidth: %d\n", biWidthOrig);
        printf("Scaled biWidth: %d\n", bi.biWidth);
        printf("Original biHeight: %d\n", biHeightOrig);
        printf("Scaled biHeight: %d\n", -bi.biHeight);


        int shrink = biWidthOrig / bi.biWidth;

        printf("Shrink %d times\n", shrink);

        for (int i = 0; i < biHeightOrig; i++)
        {
            for (int j = 0; j < biWidthOrig; j++)
            {
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                if ((j % shrink == 0) && (i % shrink == 0))
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            fseek(inptr, in_padding, SEEK_CUR);


            if (i % shrink == 0)
            {
                for (int k = 0; k < out_padding; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }

        fclose(inptr);
        fclose(outptr);
        return 0;
    }
    else
    {
        printf("Cannot scale\n");
        return 10;
    }
}

// check if ascii of a correspond to digit
int isdigit(char *a)
{
    if (((*a < 58) && (*a > 47)) || *a == 46 || *a == 45)
    {
        float temp = atof(a);
        if ((temp <= 100.0) && (temp >= 0.0))
        {
            return 0;
        }
        printf("Fatal: scale must be in range of 0.0 and 100.0\n");
        printf("Exiting...\n");
        return 1;
    }
    else
    {
        printf("Fatal: scale is not a digit\n");
        printf("Exiting...\n");
        return 1;
    }
}
