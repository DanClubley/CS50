#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const int BLOCK_SIZE = 512;     // block size for reading
typedef uint8_t BYTE;           // defining BYTE as an 8bit

int main(int argc, char *argv[])
{
    // Check that one argument is passed
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Save file
    FILE *file = fopen(argv[1], "r");

    // Check that can open file
    if (!file)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    BYTE buffer[512];           // buffer to store data being read
    int index = 0;              // JPEG index
    char *filename = malloc(8); // allocate memory for filename in format ###.JPG + \0
    FILE *img;                  // variable for image files

    // check filename is allocated
    if (!filename)
    {
        printf("Failed to allocate memory for filename");
        return 1;
    }

    // Read data in blocks of 512 bytes
    // If the block isn't 512 bytes exit while loop, end of file
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // if statement to check if first four bytes are JPEG
        // & 0xf0 - bit arithmetic to set last 4 bits to 0
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (index > 0)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", index);
            img = fopen(filename, "w"); // creates a new file called filename, in write mode
            index++;
        }
        if (index > 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    if (index > 0)
    {
        fclose(img);
    }

    free(filename);
    return 0;
}
