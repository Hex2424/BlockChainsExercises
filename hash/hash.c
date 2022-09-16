/**
 * @file hash.c
 *
 * MORE INFO ABOUT THE FILE'S CONTENTS
 *
 * @copyright This file is a part of the project beelang and is distributed under MIT license which
 * should have been included with the project. If not see: https://choosealicense.com/licenses/mit/
 *
 * @author Markas Vielavičius (markas.vielavicius@bytewall.com)
 *
 * @date 2022-09-16
 */

#include "hash.h"
#include "string.h"
#include "stdlib.h"


////////////////////////////////
// DEFINES
#define ERROR           0
#define SUCCESS         1

////////////////////////////////
// PRIVATE CONSTANTS


////////////////////////////////
// PRIVATE TYPES


////////////////////////////////
// PRIVATE METHODS

uint32_t calculateInputChecksum_(const char* input, const uint32_t inputLength);
bool generateInputSeededInitialHash_(const char* input, const uint32_t inputLength, char* output, const uint32_t outputSize);


////////////////////////////////
// IMPLEMENTATION


/**
 * @brief Public method for hashing using eHash algorithm
 * 
 * @param[in] text          input string for hashing
 * @param[out] output       output string for hashing
 * @param[in] outputSize    output size in bytes
 * @return                  Success State 
 */
bool EHash_hash(const char* text, char* output, const uint32_t outputSize)
{
    uint32_t inputLength;

    inputLength = strlen(text);
    if(!generateInputSeededInitialHash_(text, inputLength,output, outputSize))
    {
        // failed to generate initial hash
        return ERROR;
    }

    // On success
    return SUCCESS;
    
}


bool generateInputSeededInitialHash_(const char* input, const uint32_t inputLength, char* output, const uint32_t outputSize)
{
    uint32_t inputIdx;

    inputIdx = 0;

    for(uint32_t hashIdx = 0; hashIdx < outputSize; hashIdx++)
    {
        srand((int) input[inputIdx]);               // placing input bytes as seed values
        output[hashIdx] = (char) rand() % 256;      // getting remainder of 256 for random byte value

        if(inputIdx > inputLength)
        {
            inputIdx = 0;
        }else
        {
            inputIdx++;
        }

    }

    return SUCCESS;
}


/**
 * @brief Public method for calculating all input bytes values sum
 * 
 * @param[in] input         input string
 * @param[in] inputLength   input string length
 * @return                  bytes checksum number
 */
uint32_t calculateInputChecksum_(const char* input, const uint32_t inputLength)
{
    uint32_t checksum;
    checksum = 0;
    
    if(input == NULL || inputLength == 0)
    {
        // null input given
        return ERROR;
    }


    for(uint32_t inputIdx = 0; inputIdx < inputLength; inputIdx++)
    {
        checksum += input[inputIdx];
    }
    return checksum;
}