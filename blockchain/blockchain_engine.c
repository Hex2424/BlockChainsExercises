/**
 * @file blockchain_engine.c
 *
 * MORE INFO ABOUT THE FILE'S CONTENTS
 *
 * @copyright This file is a part of the project Iguana and is distributed under MIT license which
 * should have been included with the project. If not see: https://choosealicense.com/licenses/mit/
 *
 * @author Markas Vielavičius (markas.vielavicius@bytewall.com)
 *
 * @date 2022-10-24
 */
#include "blockchain_engine.h"
#include "../hash/hash.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

////////////////////////////////
// DEFINES


#define GENESIS_NULL_HASH   "ca70a0f94ee3cbe5381b7d081dcff1628bcbe8a9d9fe2a2a27230120ef10a85c"

////////////////////////////////
// PRIVATE CONSTANTS


////////////////////////////////
// PRIVATE TYPES


////////////////////////////////
// PRIVATE METHODS

static void generateHashForBlock_(BlockHandle_t block);
static void generateMerkelRootHash_(const char* prevMerkelRootHash, const char* currentBlockHash, char* resultMerkelHash);

////////////////////////////////
// IMPLEMENTATION

bool BlockchainEngine_initialize(BlockchainEngineHandle_t blockchainEngine)
{
    // blockchainEngine

    blockchainEngine->blockchain.block.header.timestamp = time(NULL);
    blockchainEngine->blockchain.block.header.difficultyTarget = 1;
    blockchainEngine->blockchain.block.header.nonce = 1;
    
    // generating merkelRootHash

    if(!EHash_hash(GENESIS_NULL_HASH,
        sizeof(GENESIS_NULL_HASH) - 1,
        blockchainEngine->blockchain.block.header.merkelRootHash,
        HASH_BYTES_LENGTH))
    {
        printf("Error occured on hashing process\n");
        return ERROR;
    }
    blockchainEngine->blockchain.block.header.merkelRootHash[HASH_BYTES_LENGTH - 1] = '\0';
    

    strcpy(blockchainEngine->blockchain.block.header.prevBlockHash, GENESIS_NULL_HASH);

    generateHashForBlock_(&blockchainEngine->blockchain.block);

    blockchainEngine->blockchain.block.blockHash[HASH_BYTES_LENGTH - 1] = '\0';
    blockchainEngine->blockchain.prevBlock = NULL;

    

    BlockchainEngine_printBlock(&blockchainEngine->blockchain.block);
    return SUCCESS;
}

static void generateHashForBlock_(BlockHandle_t block)
{
    // for(int i = 0; i < sizeof(BlockHeader_t); i++)
    // {
    //     printf("%c",((char*) &block->header)[i]);
    // }
    // printf("\n");
    // for(int i = 0; i < sizeof(BlockHeader_t); i++)
    // {
    //     char c = ((char*) &block->header)[i];
    //     if(c < '0')
    //     {
    //         printf("(");
    //     }
    //     printf("%02X ",((char*) &block->header)[i]);
    //     if(c < '0')
    //     {
    //         printf(")");
    //     }
    // }

    char forGeneration[2 * (HASH_BYTES_LENGTH - 1) + 2*(sizeof("18446744073709551615") - 1) + sizeof("256") - 1];
    sprintf(forGeneration, "%s%llo%s%llo%d", 
        block->header.merkelRootHash,
        block->header.nonce,
        block->header.prevBlockHash,
        block->header.timestamp,
        block->header.difficultyTarget
    );

    if(!EHash_hash(forGeneration,
        strlen(forGeneration),
        block->blockHash,
        HASH_BYTES_LENGTH))
    {
        printf("Error occured on hashing process\n");
        return;
    }


}


bool BlockchainEngine_printBlock(BlockHandle_t blockHandle)
{
    if(blockHandle == NULL)
    {
        return ERROR;
    }

    printf("<<###########>>\n\n bHash: %s,\n nonce:%llo\n merkelRootHash: %s\n timestamp: %llo\n prevHash: %s\n\n<<###########>>\n ", 
    blockHandle->blockHash, 
    blockHandle->header.nonce, 
    blockHandle->header.merkelRootHash,
    blockHandle->header.timestamp,
    blockHandle->header.prevBlockHash);

    srand(blockHandle->header.timestamp);

    return SUCCESS;
}

bool BlockchainEngine_mineNewBlock(BlockchainEngineHandle_t blockchainEngine)
{
    BlockchainNodeHandle_t prevBlockPointer;
    bool foundBlock = false;

    prevBlockPointer = &blockchainEngine->blockchain;

    while (true)
    {
        if(prevBlockPointer->prevBlock == NULL)
        {
            break;
        }
        prevBlockPointer = prevBlockPointer->prevBlock;
    }

    BlockchainNodeHandle_t newNode;

    newNode = malloc(sizeof(BlockchainNode_t));
    if(newNode == NULL)
    {
        return ERROR;
    }
    newNode->block.header.timestamp = time(NULL);

    generateMerkelRootHash_(
        prevBlockPointer->block.header.merkelRootHash,
        prevBlockPointer->block.header.prevBlockHash,
        newNode->block.header.merkelRootHash
    );

    newNode->block.header.difficultyTarget = 5;
    memcpy(newNode->block.header.prevBlockHash, prevBlockPointer->block.blockHash, HASH_BYTES_LENGTH);
    newNode->block.header.prevBlockHash[HASH_BYTES_LENGTH - 1 ] = '\0';

    

    while (true)
    {    
        // newNode->block.header.nonce = rand();
        newNode->block.header.nonce = rand();
        // printf("%d\n", newNode->block.header.nonce);

        generateHashForBlock_(&newNode->block);
        // printf("%s\n",newNode->block.blockHash);
        // BlockchainEngine_printBlock(newNode);

        for(uint8_t charIdx = 0; charIdx < newNode->block.header.difficultyTarget; charIdx++)
        {
            if(newNode->block.blockHash[HASH_BYTES_LENGTH - charIdx - 1] != '0')
            {
                foundBlock = false;
                break;
            }

            foundBlock = true;

        }
        if(foundBlock)
        {
            BlockchainEngine_printBlock(newNode);
            break;
        }

    }
    prevBlockPointer->prevBlock = newNode;
    
}


static void generateMerkelRootHash_(const char* prevMerkelRootHash, const char* currentBlockHash, char* resultMerkelHash)
{
    char buffer[(2 * HASH_BYTES_LENGTH) - 1];
    memcpy(buffer, prevMerkelRootHash, HASH_BYTES_LENGTH - 1);
    memcpy(buffer + HASH_BYTES_LENGTH - 1, currentBlockHash, HASH_BYTES_LENGTH);

    EHash_hash(buffer, (2 * HASH_BYTES_LENGTH) - 1, resultMerkelHash, HASH_BYTES_LENGTH - 1);
    resultMerkelHash[HASH_BYTES_LENGTH - 1] = '\0';

}