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


#define EXIT_SUCCESS            0
#define EXIT_NULL               -1
#define EXIT_HASH_FAIL          -2


#define HASH_SIZE               256
#define HASH_SIZE_BYTES         (HASH_SIZE / 4)


int main(int args, char** argv)
{
    char outputHash[HASH_SIZE_BYTES];

    // if(args == 1 || args > 2)
    // {
    //     printf("Program takes 1 argument - text to hash\n");
    //     return EXIT_SUCCESS;
    // }
    // if(argv[1] == NULL)
    // {
    //     return EXIT_NULL;
    // }

    if(!EHash_hash("575", outputHash, HASH_SIZE_BYTES))
    {
        printf("Hashing got failed for some reason\n");
        return EXIT_HASH_FAIL;
    }



    printf("eHash: %s\n", outputHash);

    return EXIT_SUCCESS;
}
