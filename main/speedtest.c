#include "../libs/crypto-algorithms/md2.h"
#include "../libs/crypto-algorithms/md5.h"
#include "../libs/crypto-algorithms/sha1.h"
#include "../libs/crypto-algorithms/sha256.h"
#include "../hash/hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct timeval Timeval;

Timeval start, stop;

void printMatavimaLaiko(Timeval* start, Timeval* stop)
{
    printf("%f",((stop->tv_sec - start->tv_sec) * 1000000 + stop->tv_usec - start->tv_usec)/1000000.0);
}

#define COUNT_INTERRUPT(stop, start, function) \
gettimeofday(start, NULL); function; gettimeofday(stop, NULL);printMatavimaLaiko(start, stop)




void initializeCtxes(MD2_CTX* md2, MD5_CTX* md5, SHA1_CTX* sha1, SHA256_CTX* sha256)
{
    md2_init(md2);
    md5_init(md5);
    sha1_init(sha1);
    sha256_init(sha256);
}

void calculateHashes(char* buffer, uint32_t length, MD2_CTX* md2, MD5_CTX* md5, SHA1_CTX* sha1, SHA256_CTX* sha256)
{
    char output[64] = {0};

    initializeCtxes(md2, md5, sha1, sha256);
    printf("%d,", length);
    // md2 
    COUNT_INTERRUPT(&stop, &start,
        md2_update(md2, buffer, length);
	    md2_final(md2, output);
    );

    printf(",");


    // md5
    COUNT_INTERRUPT(&stop, &start,
        md5_update(md5, buffer, length);
	    md5_final(md5, output);
    );

    printf(",");


    // sha1
    COUNT_INTERRUPT(&stop, &start,
        sha1_update(sha1, buffer, length);
	    sha1_final(sha1, output);
    );

    printf(",");


    // sha256
    COUNT_INTERRUPT(&stop, &start,
        sha256_update(sha256, buffer, length);
	    sha256_final(sha256, output);
    );

    printf(",");

    COUNT_INTERRUPT(&stop, &start,
        EHash_hash(buffer, length, output, 64);
    );

    printf("\n");

}

int main()
{
    MD2_CTX md2_ctx;
    MD5_CTX md5_ctx;
    SHA1_CTX sha1_ctx;
    SHA256_CTX sha256_ctx;

    srand(156);
    printf("size,md2,md5,sha1,sha256,ehash\n");

    // generating random array
    for(int i = 1;i < 10000000; i *= 2)
    {
        char* buffer = malloc(i);

        if(buffer == NULL)
        {
            exit(0);
        }

        for(int j = 0; j < i; j++)
        {
            buffer[j] = rand() % 59 + 33; // range 33 - 92 readable character buffer
        }

        calculateHashes(buffer, i, &md2_ctx, &md5_ctx, &sha1_ctx, &sha256_ctx);

        free(buffer);
    }

	// md2_update(&ctx, text1, strlen(text1));
	// md2_final(&ctx, buf);




}