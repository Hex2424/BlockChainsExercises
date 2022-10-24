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



////////////////////////////////
// IMPLEMENTATION

bool BlockchainEngine_initialize(BlockchainEngineHandle_t blockchainEngine)
{
    // blockchainEngine

    blockchainEngine->blockchain.block.header.timestamp = time(NULL);
    blockchainEngine->blockchain.block.header.difficultyTarget = 1;
    blockchainEngine->blockchain.block.header.nonce = 0;
    
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

    if(!EHash_hash(&blockchainEngine->blockchain.block.header,
        sizeof(BlockHeader_t),
        blockchainEngine->blockchain.block.blockHash,
        HASH_BYTES_LENGTH))
    {
        printf("Error occured on hashing process\n");
        return ERROR;
    }
    blockchainEngine->blockchain.block.blockHash[HASH_BYTES_LENGTH - 1] = '\0';

    return SUCCESS;
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
    return SUCCESS;
}