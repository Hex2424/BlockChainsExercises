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
    uint32_t inputSize = 0;

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

            if(fileSize > 0)
            {
                input = malloc(fileSize);             // putting input to RAM
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
                inputSize = fileSize;

            }else
            {
                input = malloc(1);
                input[0] = 0;
                inputSize = 1;
            }



        }else
        {
            printf("Program takes 1 argument - text to hash\n");
            return EXIT_SUCCESS;
        }
    }

    if(argv[1] == NULL)
    {
        return EXIT_NULL;
    }

    if(input == NULL)
    {
        input = argv[1];
        inputSize = strlen(input);
    }
  
    if(!EHash_hash(input, inputSize, outputHash, HASH_SIZE_BYTES))
    {
        printf("Hashing got failed for some reason\n");
        return EXIT_HASH_FAIL;
    }

    printf("%s\n", outputHash);


    return EXIT_SUCCESS;
}
