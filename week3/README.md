whodunit.c:

    Usage: ./whodunit <infile> <outfile>

    This program rewrites each pixels RED color byte to reduce the RED noise in the image and decipher it.

    You can test it with clue.bmp image.   

resize.c:

    Usage: ./resize <scale> <infile> <outfile>

    This program scales up/down a BPM image.

    You can test it with small.bmp or large.bmp.

recover.c:

    Usage: ./recover <filename>

    This program recovers JPEG images from RAW file by iterating through RAW bytes and looking for JPEG headers.

