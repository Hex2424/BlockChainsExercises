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

#define HASH_BYTES_LENGTH   256 / 4

typedef struct Block_t;
typedef struct BlockHeader_t;
typedef struct BlockBody_t;
typedef struct Version_t;
typedef struct Transaction_t;
typedef struct TransactioNode_t;
typedef struct User_t;

#endif // BLOCKCHAIN_STRUCTURES_STRUCTURES_H_