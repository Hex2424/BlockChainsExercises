/**
 * @file main.c
 *
 * MORE INFO ABOUT THE FILE'S CONTENTS
 *
 * @copyright This file is a part of the project beelang and is distributed under MIT license which
 * should have been included with the project. If not see: https://choosealicense.com/licenses/mit/
 *
 * @author Markas Vielavičius (markas.vielavicius@bytewall.com)
 *
 * @date 2022-09-15
 */
#include "../hash/hash.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define EXIT_SUCCESS            0
#define EXIT_NULL               -1
#define EXIT_HASH_FAIL          -2


#define HASH_SIZE               256
#define HASH_SIZE_BYTES         (HASH_SIZE / 4)


int main(int args, char** argv)
{
    char outputHash[HASH_SIZE_BYTES] = {0};
    char* input = NULL;

    if(args == 1)
    {
        printf("Program takes 1 argument - text to hash\n");
        return EXIT_SUCCESS;

    }


    if(args > 2)
    {
        if(strcmp(argv[1], "-f") == 0) // failo ivedimo argumento patikra
        {
            FILE* file = fopen(argv[2], "r");

            if(file == NULL)
            {
                printf("Could not find mentioned file: %s\n", argv[2]);
                return EXIT_SUCCESS;
            }


            fseek(file,0L, SEEK_END);
            int fileSize = ftell(file);
            rewind(file);
            input = malloc(fileSize);               // putting input to RAM

            if(input == NULL)
            {
                printf("Failed to allocate buffer for file size: %d\n", fileSize);
                return EXIT_SUCCESS;
            }

            if(fread(input, 1, fileSize, file) != fileSize)
            {
                printf("Failed to read mentioned file: %s\n", argv[2]);
                return EXIT_SUCCESS;
            }
        }else
        {
            printf("Program takes 1 argument - text to hash\n");
            return EXIT_SUCCESS;
        }
    }

    if(input == NULL)
    {
        input = argv[1];
    }
  
    if(argv[1] == NULL)
    {
        return EXIT_NULL;
    }

    //  for(int i = 0; i < HASH_SIZE_BYTES; i++)
    // {
    //     printf("%02X ", (uint8_t) outputHash[i]);
    // }
    // printf("\n");

    if(!EHash_hash(input, outputHash, HASH_SIZE_BYTES))
    {
        printf("Hashing got failed for some reason\n");
        return EXIT_HASH_FAIL;
    }

    // for(int i = 0; i < HASH_SIZE_BYTES; i++)
    // {
    //     printf("%d ", outputHash[i]);
    // }
    printf("%s\n", outputHash);
    // printf("eHash: %s\n", outputHash);

    return EXIT_SUCCESS;
}
