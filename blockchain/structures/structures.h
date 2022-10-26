/**
 * @file structures.h
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

#ifndef BLOCKCHAIN_STRUCTURES_STRUCTURES_H_
#define BLOCKCHAIN_STRUCTURES_STRUCTURES_H_

#include <stdint.h>
#include <stdbool.h>

#define HASH_BYTES_LENGTH   256 / 4 + 1
#define GENESIS_NULL_HASH   "ca70a0f94ee3cbe5381b7d081dcff1628bcbe8a9d9fe2a2a27230120ef10a85c"
#define MAX_USERS           1000
#define MAX_TRANSACTIONS    10000

#define SUCCESS 1
#define ERROR   0

typedef struct transnode TransactionNode_t;
typedef struct transnode* TransactionNodeHandle_t;

typedef struct blockchnode BlockchainNode_t;
typedef struct blockchnode * BlockchainNodeHandle_t;

typedef struct
{
    uint8_t major;
    uint8_t minor;
}Version_t;


typedef struct
{
    char prevBlockHash[HASH_BYTES_LENGTH];
    char merkelRootHash[HASH_BYTES_LENGTH];
    uint64_t nonce;
    uint64_t timestamp;
    uint8_t difficultyTarget;
    
}BlockHeader_t;


typedef struct 
{
    char transactionId[HASH_BYTES_LENGTH];
    char sender[HASH_BYTES_LENGTH];
    char receiver[HASH_BYTES_LENGTH];
    uint64_t sum;
}Transaction_t;



struct transnode
{
    Transaction_t transaction;
    TransactionNodeHandle_t nextTransaction;
};


typedef struct 
{
    TransactionNodeHandle_t transactionChain;
    uint32_t currentLength;
}TransactionsPool_t;


typedef struct
{
    TransactionNode_t transactions;
    uint32_t transactionsCount;
}BlockBody_t;

typedef struct
{
    char blockHash[HASH_BYTES_LENGTH];
    BlockHeader_t header;
    BlockBody_t body;
}Block_t;

typedef struct
{   
    char publicKey[HASH_BYTES_LENGTH];
    uint64_t name;
    int64_t balance;   
}User_t;

struct blockchnode
{
    Block_t block;
    BlockchainNodeHandle_t prevBlock;
};

typedef struct 
{
    BlockchainNode_t blockchain;
    User_t users[MAX_USERS];
    TransactionsPool_t transactionsPool;
}BlockchainEngine_t;

typedef BlockchainEngine_t* BlockchainEngineHandle_t;
typedef Block_t* BlockHandle_t;
typedef TransactionsPool_t* TransactionsPoolHandle_t;
typedef Transaction_t* TransactionHandle_t;

#endif // BLOCKCHAIN_STRUCTURES_STRUCTURES_H_