/**
 * @file structures.c
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

#include "structures.h"

////////////////////////////////
// DEFINES


////////////////////////////////
// PRIVATE CONSTANTS


////////////////////////////////
// PRIVATE TYPES

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

    BlockHeader_t header;
    BlockBody_t body;
    
}Block_t;

typedef struct
{   
    char publicKey[HASH_BYTES_LENGTH];
    uint64_t name;
    int64_t balance;   
}User_t;

typedef struct
{
    Block_t block;
    BlockchainEngineHandle_t prevBlock;
}BlockchainNode_t;

typedef struct 
{
    BlockchainNode_t blockchain;
}BlockchainEngine_t;




////////////////////////////////
// PRIVATE METHODS


////////////////////////////////
// IMPLEMENTATION

