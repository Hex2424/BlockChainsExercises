/**
 * @file blockchain_engine.h
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

#ifndef BLOCKCHAIN_BLOCKCHAIN_ENGINE_H_
#define BLOCKCHAIN_BLOCKCHAIN_ENGINE_H_
#include "structures/structures.h"


bool BlockchainEngine_initialize(BlockchainEngineHandle_t blockchainEngine);
bool BlockchainEngine_printBlock(BlockHandle_t blockHandle);
BlockchainNodeHandle_t BlockchainEngine_getLatestBlockNode(BlockchainEngineHandle_t blockchainEngine);
BlockchainNodeHandle_t BlockchainEngine_mineNewBlock(BlockchainEngineHandle_t blockchainEngine, BlockchainNodeHandle_t latestBlockNode);
#endif // BLOCKCHAIN_BLOCKCHAIN_ENGINE_H_