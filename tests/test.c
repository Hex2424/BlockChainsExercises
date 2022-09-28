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
            return i;
        }
        /* code */
    }
    
}


int main()
{
    struct timeval start, stop;
    char* input;
    char output[64];

    FILE* file = fopen("../test_files/LT-Top500k.txt", "r");
    fseek(file,0L, SEEK_END);
    int fileSize = ftell(file);
    input = malloc(fileSize);
    rewind(file);
    fread(input, 1, fileSize, file);



    // for(int i = 1; i < 500000; i *= 2)
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