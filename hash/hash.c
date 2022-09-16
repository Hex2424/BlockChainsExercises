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

static uint32_t calculateInputChecksum_(const char* input, const uint32_t inputLength);
static bool generateInputSeededInitialHash_(const char* input, const uint32_t inputLength, char* output, const uint32_t outputSize);
static bool apply1BitSlidingAlgorithm_(const char* input, const uint32_t inputLength, char* output, const uint32_t outputSize);

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

    if(!apply1BitSlidingAlgorithm_(text, inputLength, output, outputSize))
    {
        // failed to calculate via sliding bit method
        return ERROR;
    }


    // On success
    return SUCCESS;
    
}


static bool apply1BitSlidingAlgorithm_(const char* input, const uint32_t inputLength, char* output, const uint32_t outputSize)
{
    uint8_t slidingMask;
    uint32_t inputIdx;

    slidingMask = 00000001; 
    inputIdx = 0;

    if(output == NULL || input == NULL || outputSize == 0 || inputLength == 0)
    {
        // something wrong with function input, may be heap leak
        return ERROR;
    }



    for(uint32_t outputIdx = 0; outputIdx < outputSize; outputIdx++)
    {
        if(slidingMask == 128)         
        {
            slidingMask = 00000001; // when sliding mask reaches 1000 0000 byte state, should refresh to 0000 0001
        }
        
        if(inputIdx > inputLength)
        {
            inputIdx = 0;           // overlooping input byte idx
        }

        for(uint32_t outputIdx2nd = 0; outputIdx2nd < outputSize; outputIdx2nd++)
        {
            output[outputIdx2nd] ^= (input[inputIdx] & slidingMask);
            // mask gets applied to input first letter with and so we get 1 bit of input letter, 
            // which we XOR with output letter / byte and continue, sliding mask keeps changing, so whole input makes importance to result.
        }
        slidingMask <<= 1;  // moving sliding mask ex: 00000010 << 00000001 ...
        inputIdx++;
    }

    return SUCCESS;
}



static bool generateInputSeededInitialHash_(const char* input, const uint32_t inputLength, char* output, const uint32_t outputSize)
{
    uint32_t inputIdx;

    inputIdx = 0;

    srand(calculateInputChecksum_(input, inputLength));     // placing input string bytes checksum as random seed

    for(uint32_t hashIdx = 0; hashIdx < outputSize; hashIdx++)
    {
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
static uint32_t calculateInputChecksum_(const char* input, const uint32_t inputLength)
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