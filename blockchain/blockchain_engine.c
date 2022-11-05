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
static bool generateMerkelTreeHashFromBlockchain_(const BlockchainEngineHandle_t engine, char* merkelHash);
static struct tm* getTimeAndDate_(uint64_t milliseconds);
static void generateRandomTransactions_(BlockchainEngineHandle_t blockchainEngine);
void tryAddTransactionsToBlock_(BlockchainEngineHandle_t blockchainEngine, uint32_t count);
static void updateUsersBalanceByTransaction_(BlockchainEngineHandle_t blockchainEngine, TransactionNodeHandle_t transactionNode);
static bool fillUsersFromFile_(BlockchainEngineHandle_t blockchainEngine, const char* filename);
////////////////////////////////
// IMPLEMENTATION

bool BlockchainEngine_initialize(BlockchainEngineHandle_t blockchainEngine)
{
    // blockchainEngine
    srand(time(NULL));
    if(!fillUsersFromFile_(blockchainEngine, "../blockchain/blockchainFiles/users"))
    {
        printf("Please fill users to blockchain firstly before running transaction adding tests\n");
        return ERROR;
    }

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
    blockchainEngine->blockchain.nextBlock = NULL;
    TransactionsPool_initialize(&blockchainEngine->blockchain.block.body.transactionsPool);

    BlockchainEngine_printBlock(&blockchainEngine->blockchain.block);

    // generateRandomUsers_(blockchainEngine);

    
    TransactionsPool_initialize(&blockchainEngine->transactionsPool);
    generateRandomTransactions_(blockchainEngine);

    
    tryAddTransactionsToBlock_(blockchainEngine, MAX_TRANSACTIONS);

    return SUCCESS;
}

static bool fillUsersFromFile_(BlockchainEngineHandle_t blockchainEngine, const char* filename)
{
    FILE* usersFile;
    usersFile = fopen(filename, "r");
    if(usersFile == NULL)
    {
        return ERROR;
    }
    fread(blockchainEngine->users,1, sizeof(User_t) * MAX_USERS, usersFile);
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
    
    if(!generateMerkelTreeHashFromBlockchain_(blockchainEngine, newNode->block.header.merkelRootHash))
    {
        return NULL;
    }
    
    newNode->block.header.difficultyTarget = 5;
    memcpy(newNode->block.header.prevBlockHash, latestBlockNode->block.blockHash, HASH_BYTES_LENGTH);
    newNode->block.header.prevBlockHash[HASH_BYTES_LENGTH - 1 ] = '\0';

    
    printf("[>>] Mining block:\n");
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
                break; printf("[>>] Mining block:\n");
            }

            foundBlock = true;

        }
        if(foundBlock)
        {
            BlockchainEngine_printBlock(newNode);
            break;
        }

    }
    return newNode;
    
}

BlockchainNodeHandle_t BlockchainEngine_getLatestBlockNode(BlockchainEngineHandle_t blockchainEngine)
{
    BlockchainNodeHandle_t lastNode;

    lastNode = &blockchainEngine->blockchain;
    if(lastNode == NULL)
    {
        return NULL;
    }
    
    while (true)
    {
        if(lastNode->nextBlock == NULL)
        {
            break;
        }
        lastNode = lastNode->nextBlock;
    }
    return lastNode;
}

uint32_t BlockchainEngine_getSize(BlockchainEngineHandle_t blockchainEngine)
{
    BlockchainNodeHandle_t lastNode;
    uint32_t size;
    size = 0;

    lastNode = &blockchainEngine->blockchain;
    
    while (true)
    {
        size++;
        if(lastNode->nextBlock == NULL)
        {
            break;
        }
        lastNode = lastNode->nextBlock;
    }
    return size;
}

static bool generateMerkelTreeHashFromBlockchain_(const BlockchainEngineHandle_t engine, char* merkelHash)
{
    MerkelNodeHandle_t nodesList;
    uint32_t merkelTreeSize;
    uint16_t merkelRootLayersCount;
    BlockchainNodeHandle_t currentNode;

    merkelTreeSize = BlockchainEngine_getSize(engine);
    nodesList = malloc(merkelTreeSize * sizeof(MerkelNode_t));
    if(nodesList == NULL)
    {
        // incase of failed malloc
        return ERROR;
    }

    merkelRootLayersCount = (merkelTreeSize + 1) / 2;
    currentNode = &engine->blockchain;

    for(uint32_t i = 0; i < merkelTreeSize; i++)
    {
        nodesList[i].left = NULL;
        nodesList[i].right = NULL;
        strcpy(nodesList[i].merkelHash, currentNode->block.blockHash);
        currentNode = currentNode->nextBlock;
    }
    
    while (true)
    {
        uint32_t nodeIdx = 0;
        for(uint32_t i = 0; i < merkelTreeSize; i += 2, nodeIdx++)
        {
            char buffer[(2 * HASH_BYTES_LENGTH) - 1];
            memcpy(buffer, nodesList[i].merkelHash, HASH_BYTES_LENGTH - 1);
            // nodesList[nodeIdx].left = nodesList[i];

            if((i + 1) < merkelTreeSize)
            {
                // has pair
                memcpy(buffer + HASH_BYTES_LENGTH - 1, nodesList[i + 1].merkelHash, HASH_BYTES_LENGTH);
                // nodesList[nodeIdx].right = nodesList[i + 1];

            }else if(merkelRootLayersCount == 0)
            {
                // no pair, ended hashing
                strcpy(merkelHash, nodesList[0].merkelHash);
                free(nodesList);
                return SUCCESS;
            }else
            {
                // same hash apply if no pair
                memcpy(buffer + HASH_BYTES_LENGTH - 1, nodesList[i].merkelHash, HASH_BYTES_LENGTH);
                // nodesList[nodeIdx].right = nodesList[i];
            }
            

            EHash_hash(buffer, (2 * HASH_BYTES_LENGTH) - 1, nodesList[nodeIdx].merkelHash, HASH_BYTES_LENGTH - 1);
            nodesList[nodeIdx].merkelHash[HASH_BYTES_LENGTH - 1] = '\0';
        }
        merkelTreeSize = nodeIdx + 1;
        merkelRootLayersCount--;
        if(merkelRootLayersCount == 0)
        {
            strcpy(merkelHash, nodesList[0].merkelHash);
            free(nodesList);
            return SUCCESS;
        }
    }
    

}


static struct tm* getTimeAndDate_(uint64_t milliseconds)
{
    time_t seconds = (time_t)(milliseconds / 1000);
    return (struct tm*) localtime(&milliseconds);
}

void BlockchainEngine_generateRandomUsers(BlockchainEngineHandle_t blockchainEngine)
{
    FILE* usersFile;
    usersFile = fopen("../blockchain/blockchainFiles/users", "w");
    for(size_t userIdx = 0; userIdx < MAX_USERS; userIdx++)
    {
        blockchainEngine->users[userIdx].name = rand(); // username is a number representing user id
        EHash_hash(&blockchainEngine->users[userIdx].name,
        sizeof(uint64_t),
        blockchainEngine->users[userIdx].publicKey,
        HASH_BYTES_LENGTH - 1);
        blockchainEngine->users[userIdx].publicKey[HASH_BYTES_LENGTH - 1] = '\0';
        blockchainEngine->users[userIdx].balance = rand() % 999900 + 100;           // 100 - 1000000 balance

        printf("[>>] Generating user%d:\n\tname:%llo,\n\tpublicKey:%s,\n\tbalance:%llo\n\n",
        userIdx,
        blockchainEngine->users[userIdx].name,
        blockchainEngine->users[userIdx].publicKey,
        blockchainEngine->users[userIdx].balance);

        fwrite(blockchainEngine->users + userIdx, 1, sizeof(User_t), usersFile);
    }
    fclose(usersFile);
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

void tryAddTransactionsToBlock_(BlockchainEngineHandle_t blockchainEngine, uint32_t count)
{
    for(uint32_t i = 0; i < count; i++)
    {
        TransactionNodeHandle_t transactionNode;
        transactionNode = TransactionsPool_pop(&blockchainEngine->transactionsPool, rand() % blockchainEngine->transactionsPool.currentLength);
        if(transactionNode == NULL)
        {
            return;
        }

        BlockchainNodeHandle_t blockContainer;
        blockContainer = BlockchainEngine_getLatestBlockNode(blockchainEngine);
        if(blockContainer == NULL)
        {
            return;
        }
        // printf("[>>] Trying add transaction to latest block\n");
        // TransactionsPool_printTransaction(transactionNode);
        if(blockContainer->block.body.transactionsPool.currentLength < MAX_TRANSACTIONS_IN_BLOCK)
        {
            TransactionsPool_addNewTransaction(&blockContainer->block.body.transactionsPool, transactionNode);
        }else
        {
            // transactions full - need mine new block
            BlockchainNodeHandle_t minedBlockNode;
            minedBlockNode = BlockchainEngine_mineNewBlock(blockchainEngine, blockContainer);
            if(minedBlockNode == NULL)
            {
                return;
            }
            // mined block is successful
            // putting transactions in new block
            TransactionsPool_initialize(&minedBlockNode->block.body.transactionsPool);
            if(TransactionsPool_addNewTransaction(&minedBlockNode->block.body.transactionsPool, transactionNode))
            {
                updateUsersBalanceByTransaction_(blockchainEngine, transactionNode);
                blockContainer->nextBlock = minedBlockNode;
            }
            
        }

    }
}

static void updateUsersBalanceByTransaction_(BlockchainEngineHandle_t blockchainEngine, TransactionNodeHandle_t transactionNode)
{
    for(size_t userIdx = 0; userIdx < MAX_USERS; userIdx++)
    {
        if(strcmp(blockchainEngine->users[userIdx].publicKey, transactionNode->transaction.sender) == 0)
        {
            blockchainEngine->users[userIdx].balance -= transactionNode->transaction.sum;
            continue;
        }

        if(strcmp(blockchainEngine->users[userIdx].publicKey, transactionNode->transaction.receiver) == 0)
        {
            blockchainEngine->users[userIdx].balance += transactionNode->transaction.sum;
        }
    }
}