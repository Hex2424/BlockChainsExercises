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
#include "printf.h"

int main(int args, char** argv)
{
    BlockchainEngine_t engine;

    if(!BlockchainEngine_initialize(&engine))
    {
        printf("Failed to initialize blockchain engine\n");
        return -1;
    }

    BlockchainEngine_printBlock(&engine.blockchain.block);

}
