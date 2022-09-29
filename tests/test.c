/**
 * @file test.c
 *
 * MORE INFO ABOUT THE FILE'S CONTENTS
 *
 * @copyright This file is a part of the project beelang and is distributed under MIT license which
 * should have been included with the project. If not see: https://choosealicense.com/licenses/mit/
 *
 * @author Markas Vielavičius (markas.vielavicius@bytewall.com)
 *
 * @date 2022-09-29
 */
#include "../hash/hash.h"
#include <stdio.h>
#include <sys/time.h>
#include "stdlib.h"
#include "string.h"

typedef struct timeval Timeval;

void printMatavimaLaiko(Timeval* start, Timeval* stop)
{
    //printf("Uztruko %f s\n",((stop->tv_sec - start->tv_sec) * 1000000 + stop->tv_usec - start->tv_usec)/1000000.0);
}

#define COUNT_INTERRUPT(stop, start, function) \
gettimeofday(start, NULL); function; gettimeofday(stop, NULL);printMatavimaLaiko(start, stop)

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

int calculateSymbolsUntilOccuranceRepeat(int nTimes, char* input,int inputSize, char occuranceToFind)
{
    int i = 0;
    int occurances = 0;

    for(int i = 0; i < inputSize;i++)
    {
        if(input[i] == occuranceToFind)
        {
            occurances++;
        }

        if(occurances == nTimes)
        {
            return i + 1;
        }
        /* code */
    }
    
}



int main()
{
    struct timeval start, stop;
    char* input;
    char output[64];
    char output2[64];
    unsigned int mask = 00000001;
    int bitLevelOccurances = 0;
    int byteLevelOccurances = 0;
    int lines = 0;

    FILE* file = fopen("../test_files/data_poros.txt", "r");
    fseek(file,0L, SEEK_END);
    int fileSize = ftell(file);
    input = malloc(fileSize);
    rewind(file);
    fread(input, 1, fileSize, file);
    int lineLength;

    for(char* currentLinePointer = input; currentLinePointer < (input + fileSize);)
    {
        int lineLength;
        lineLength = calculateSymbolsUntilOccuranceRepeat(1, currentLinePointer, fileSize, '\n');
        if(lineLength == 0)
        {
            exit(0);
        }
        // printf("%d .. \n", lineLength);
        EHash_hash(currentLinePointer, lineLength, output, sizeof(output));
        lines++;
        currentLinePointer += lineLength;
        if(currentLinePointer >= (input + fileSize))
        {
            exit(0);
        }
        lineLength = calculateSymbolsUntilOccuranceRepeat(1, currentLinePointer, fileSize, '\n');
        EHash_hash(currentLinePointer, lineLength, output2, sizeof(output2));
        lines++;
        currentLinePointer += lineLength;
        // printf("%d .. \n", lineLength);
        // printf("%s\n%s\n", output, output2);
        for(int j = 0; j < sizeof(output);j++)
        {
            if(output[j] == output2[j])
            {
                // byte level occurances
                byteLevelOccurances++;
            }
            unsigned int xoredEquals = output[j] ^ output2[j];
            // printf("Xored result: %d\n", xoredEquals);
            for(int z = 0; z < 8;z++)
            {
                // printf("HMM:%d\n", xoredEquals);
                if(((xoredEquals) & mask) == 0)
                {
                    bitLevelOccurances++;
                }

                xoredEquals >>= 1;

            }
            bitLevelOccurances--;
            // printf("bitsCol: %d\n", bitLevelOccurances);


        }
        

    }
    printf("Bytes: %d/%f, BITS: %d/%f, Lines:%d\n",byteLevelOccurances, byteLevelOccurances / (64.0f*(lines/2)), bitLevelOccurances,bitLevelOccurances / ( 8* 64.0f*(lines/2)), lines);
    // COUNT_INTERRUPT(&stop, &start,
    // for(int j = 0; j < 5; j++)
    //     {
    //         EHash_hash(input, fileSize, output, sizeof(output));
    //     }
    // );





    // printf("%s\n", output);
    // for(int i = 1; i < 1000; i *= 2)
    // {

    //     int lengthToRead = calculateSymbolsUntilOccuranceRepeat(i, input, fileSize, '\n');
        
    //     float vidurkis = 0;

    //      COUNT_INTERRUPT(&stop, &start,

    //         for(int j = 0; j < 5; j++)
    //         {
    //             EHash_hash(input, lengthToRead, output, sizeof(output));
    //         }
    //     );
    //     // printMatavimaLaiko(&start, &stop);
    //     //printf("eil:%d, laikas:%f %s\n\n",i,(((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000000.0)/5, output);
    //     printf("%d,%f\n",i,(((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000000.0)/5);

    // }
}