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
#include "../blockchain/blockchain_engine.h"
#include "stdio.h"

int main(int args, char** argv)
{
    if(args == 1 || (strcmp(argv[1], "-help") == 0) || (strcmp(argv[1], "-h") == 0))
    {
        // help command
        FILE* header;
        char c;
        header = fopen("../blockchain/GUI/eblockchain_header.txt", "r");
        if(header == NULL)
        {
            return -1;
        }
        int readed = 1;
        while (readed > 0)
        {
            readed = fread(&c, 1, 1, header);
            printf("%c", c);
        }

        return 0;
    }
    BlockchainEngine_t engine;
    if(strcmp(argv[1], "-gen_rand_users") == 0)
    {
        // generate random users
        BlockchainEngine_generateRandomUsers(&engine);
        return 0;
    }

    if(strcmp(argv[1], "-run_testing") == 0)
    {
        // generate random users
        BlockchainEngine_initialize(&engine);
        return 0;
    }
    BlockchainEngine_initialize(&engine);
    // if(strcmp(argv[1], "-gen_rand_trans") == 0)


    // if(!BlockchainEngine_initialize(&engine))
    // {
    //     printf("Failed to initialize blockchain engine\n");
    //     return -1;
    // }

    
    // while (true)
    // {
    //     BlockchainEngine_mineNewBlock(&engine);
    // }
    

}
