/**
 * @file transactions.h
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
#ifndef BLOCKCHAIN_TRANSACTIONS_TRANSACTIONS_H_
#define BLOCKCHAIN_TRANSACTIONS_TRANSACTIONS_H_

#include "../structures/structures.h"

TransactionNodeHandle_t TransactionsPool_getLastTransactionNode(TransactionsPoolHandle_t transPool);
TransactionNodeHandle_t TransactionsPool_createNewTransactionNode();
void TransactionsPool_initialize(TransactionsPoolHandle_t transPool);
bool TransactionsPool_addNewTransaction(TransactionsPoolHandle_t transPool, TransactionNodeHandle_t transactionNodeToAdd);
void TransactionsPool_printTransaction(TransactionNodeHandle_t transactionNode);
TransactionNodeHandle_t TransactionsPool_GetTransactionById(TransactionsPoolHandle_t transPool, const char* transactionID);
TransactionNodeHandle_t TransactionsPool_getNthTransactionNode(TransactionsPoolHandle_t transPool, uint32_t idx);
TransactionNodeHandle_t TransactionsPool_pop(TransactionsPoolHandle_t transPool, uint32_t idx);
#endif // BLOCKCHAIN_TRANSACTIONS_TRANSACTIONS_H_