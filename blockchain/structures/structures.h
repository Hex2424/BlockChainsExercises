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

#define SUCCESS 1
#define ERROR   0

typedef struct TransactionNode_t* TransactionNodeHandle_t;

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



typedef struct 
{
    Transaction_t transaction;
    TransactionNodeHandle_t prevTransaction;
}TransactionNode_t;


typedef struct
{
    TransactionNode_t transactions;
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
}BlockchainEngine_t;

typedef BlockchainEngine_t* BlockchainEngineHandle_t;
typedef Block_t* BlockHandle_t;


#endif // BLOCKCHAIN_STRUCTURES_STRUCTURES_H_