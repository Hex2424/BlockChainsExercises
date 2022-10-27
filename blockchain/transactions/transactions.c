/**
 * @file transactions.c
 *
 * MORE INFO ABOUT THE FILE'S CONTENTS
 *
 * @copyright This file is a part of the project Iguana and is distributed under MIT license which
 * should have been included with the project. If not see: https://choosealicense.com/licenses/mit/
 *
 * @author Markas Vielavičius (markas.vielavicius@bytewall.com)
 *
 * @date 2022-10-27
 */
#include "transactions.h"
#include "stdlib.h"
#include "stdio.h"

////////////////////////////////
// DEFINES


////////////////////////////////
// PRIVATE CONSTANTS


////////////////////////////////
// PRIVATE TYPES


////////////////////////////////
// PRIVATE METHODS


////////////////////////////////
// IMPLEMENTATION

void TransactionsPool_initialize(TransactionsPoolHandle_t transPool)
{
    transPool->currentLength = 0;
    transPool->transactionChain = TransactionsPool_createNewTransactionNode();
}


TransactionNodeHandle_t TransactionsPool_createNewTransactionNode()
{
    return malloc(sizeof(TransactionNode_t));
}


bool TransactionsPool_addNewTransaction(TransactionsPoolHandle_t transPool, TransactionNodeHandle_t transactionNodeToAdd)
{
    TransactionNodeHandle_t lastTransactionNode;
    lastTransactionNode = TransactionsPool_getLastTransactionNode(transPool);
    if(lastTransactionNode == NULL)
    {
        return ERROR;
    }

    lastTransactionNode->nextTransaction = transactionNodeToAdd;
    transPool->currentLength++;
    return SUCCESS;
}


TransactionNodeHandle_t TransactionsPool_getLastTransactionNode(TransactionsPoolHandle_t transPool)
{
    return TransactionsPool_getNthTransactionNode(transPool, transPool->currentLength);
}

TransactionNodeHandle_t TransactionsPool_getNthTransactionNode(TransactionsPoolHandle_t transPool, uint32_t idx)
{
    TransactionNodeHandle_t transactionNode = transPool->transactionChain;

    for(uint32_t i = 0; i < idx; i++)
    {
        transactionNode = transactionNode->nextTransaction;
    }

    return transactionNode;
}




TransactionNodeHandle_t TransactionsPool_GetTransactionById(TransactionsPoolHandle_t transPool, const char* transactionID)
{
    TransactionNodeHandle_t transactionNode = transPool->transactionChain;

    if(strcmp(transactionNode->transaction.transactionId,transactionID) == 0)
    {
        return transactionNode;
    }

    for(uint32_t i = 0; i < transPool->currentLength; i++)
    {
        transactionNode = transactionNode->nextTransaction;
        if(strcmp(transactionNode->transaction.transactionId, transactionID) == 0)
        {
            return transactionNode;
        }
    }

    return NULL;
}

TransactionNodeHandle_t TransactionsPool_pop(TransactionsPoolHandle_t transPool, uint32_t idx)
{
    TransactionNodeHandle_t transactionNode = transPool->transactionChain;
    TransactionNodeHandle_t prev;
    for(uint32_t i = 0; i < idx; i++)
    {
        prev = transactionNode;
        transactionNode = transactionNode->nextTransaction;

    }
    if(prev == NULL)
    {
        transPool->transactionChain->nextTransaction = NULL;
    }else
    {
        prev->nextTransaction = transactionNode->nextTransaction;
    }
    transPool->currentLength--;
    return transactionNode;
}


bool TransactionsPool_removeTransaction(TransactionsPoolHandle_t transPool, const char* transactionID)
{

}

void TransactionsPool_printTransaction(TransactionNodeHandle_t transactionNode)
{
    if(transactionNode == NULL)
    {
        printf("<<Transaction(NULL)>>\n");
    }

    printf("<<Transaction>>\n\n transactionID:%s,\n sender:%s,\n receiver:%s\n transmitSum:%d\n\n<<Transaction>>\n",
    transactionNode->transaction.transactionId,
    transactionNode->transaction.sender,
    transactionNode->transaction.receiver,
    transactionNode->transaction.sum);
}