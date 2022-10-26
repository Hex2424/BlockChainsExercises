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
#include "transactions/transactions.h"

////////////////////////////////
// DEFINES


////////////////////////////////
// PRIVATE CONSTANTS


////////////////////////////////
// PRIVATE TYPES


////////////////////////////////
// PRIVATE METHODS

static void generateHashForBlock_(BlockHandle_t block);
static void generateMerkelRootHash_(const char* prevMerkelRootHash, const char* currentBlockHash, char* resultMerkelHash);
static struct tm* getTimeAndDate_(uint64_t milliseconds);
static void generateRandomUsers_(BlockchainEngineHandle_t blockchainEngine);
static void generateRandomTransactions_(BlockchainEngineHandle_t blockchainEngine);
////////////////////////////////
// IMPLEMENTATION

bool BlockchainEngine_initialize(BlockchainEngineHandle_t blockchainEngine)
{
    // blockchainEngine
    srand(time(NULL));
    
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

    generateRandomUsers_(blockchainEngine);

    
    TransactionsPool_initialize(&blockchainEngine->transactionsPool);
    generateRandomTransactions_(blockchainEngine);


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

    // char forGeneration[2 * (HASH_BYTES_LENGTH - 1) + 2*(sizeof("18446744073709551615") - 1) + sizeof("256") - 1];
    // sprintf(forGeneration, "%s%llo%s%llo%d", 
    //     block->header.merkelRootHash,
    //     block->header.nonce,
    //     block->header.prevBlockHash,
    //     block->header.timestamp,
    //     block->header.difficultyTarget
    // );

    if(!EHash_hash(&block->header,
        sizeof(block->header),
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
    // struct tm* date;
    // date = getTimeAndDate_(blockHandle->header.timestamp);
    
    printf("<<Block>>\n\n bHash: %s,\n nonce:%llo\n merkelRootHash: %s\n timestamp: %llo\n prevHash: %s\n\n<<Block>>\n", 
    blockHandle->blockHash, 
    blockHandle->header.nonce, 
    blockHandle->header.merkelRootHash,
    blockHandle->header.timestamp,
    // asctime(date),
    blockHandle->header.prevBlockHash);

    return SUCCESS;
}

BlockchainNodeHandle_t BlockchainEngine_mineNewBlock(BlockchainEngineHandle_t blockchainEngine, BlockchainNodeHandle_t latestBlockNode)
{
    bool foundBlock = false;
    BlockchainNodeHandle_t newNode;

    newNode = malloc(sizeof(BlockchainNode_t));
    if(newNode == NULL)
    {
        return NULL;
    }
    newNode->block.header.timestamp = time(NULL);

    generateMerkelRootHash_(
        latestBlockNode->block.header.merkelRootHash,
        latestBlockNode->block.header.prevBlockHash,
        newNode->block.header.merkelRootHash
    );

    newNode->block.header.difficultyTarget = 5;
    memcpy(newNode->block.header.prevBlockHash, latestBlockNode->block.blockHash, HASH_BYTES_LENGTH);
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
    
}

BlockchainNodeHandle_t BlockchainEngine_getLatestBlockNode(BlockchainEngineHandle_t blockchainEngine)
{
    BlockchainNodeHandle_t lastNode;

    lastNode = &blockchainEngine->blockchain;

    while (true)
    {
        if(lastNode->prevBlock == NULL)
        {
            break;
        }
        lastNode = lastNode->prevBlock;
    }
    return lastNode;
}



static void generateMerkelRootHash_(const char* prevMerkelRootHash, const char* currentBlockHash, char* resultMerkelHash)
{
    char buffer[(2 * HASH_BYTES_LENGTH) - 1];
    memcpy(buffer, prevMerkelRootHash, HASH_BYTES_LENGTH - 1);
    memcpy(buffer + HASH_BYTES_LENGTH - 1, currentBlockHash, HASH_BYTES_LENGTH);

    EHash_hash(buffer, (2 * HASH_BYTES_LENGTH) - 1, resultMerkelHash, HASH_BYTES_LENGTH - 1);
    resultMerkelHash[HASH_BYTES_LENGTH - 1] = '\0';

}

static struct tm* getTimeAndDate_(uint64_t milliseconds)
{
    time_t seconds = (time_t)(milliseconds / 1000);
    return (struct tm*) localtime(&milliseconds);
}

static void generateRandomUsers_(BlockchainEngineHandle_t blockchainEngine)
{
    for(size_t userIdx = 0; userIdx < MAX_USERS; userIdx++)
    {
        blockchainEngine->users[userIdx].name = rand(); // username is a number representing user id
        EHash_hash(&blockchainEngine->users[userIdx].name,
        sizeof(uint64_t),
        blockchainEngine->users[userIdx].publicKey,
        HASH_BYTES_LENGTH - 1);
        blockchainEngine->users[userIdx].publicKey[HASH_BYTES_LENGTH - 1] = '\0';
        blockchainEngine->users[userIdx].balance = rand() % 999900 + 100;           // 100 - 1000000 balance
    }
}

static void generateRandomTransactions_(BlockchainEngineHandle_t blockchainEngine)
{
    for(size_t transIdx = 0; transIdx < MAX_TRANSACTIONS; transIdx++)
    {
        User_t* senderHandle = blockchainEngine->users + (rand() % MAX_USERS);
        TransactionNodeHandle_t transNodeHandle;
        transNodeHandle = TransactionsPool_createNewTransactionNode();
        if(transNodeHandle == NULL)
        {
            return;
        }

        strcpy(transNodeHandle->transaction.sender, senderHandle->publicKey);
        strcpy(transNodeHandle->transaction.receiver, blockchainEngine->users[rand() % MAX_USERS].publicKey);

        transNodeHandle->transaction.sum = rand() % senderHandle->balance;

        EHash_hash(transNodeHandle->transaction.sender,
            sizeof(Transaction_t) - sizeof(transNodeHandle->transaction.transactionId),
            transNodeHandle->transaction.transactionId,
            HASH_BYTES_LENGTH - 1
        );
        transNodeHandle->transaction.transactionId[HASH_BYTES_LENGTH - 1] = '\0';
        TransactionsPool_addNewTransaction(&blockchainEngine->transactionsPool, transNodeHandle);
    }
}