#include <stdio.h>
#include <stdlib.h>

enum {ID=0, MAX_DAYS=10001};

#define FOR(i, b, e) for((i)=(b); (i)<(e); ++(i))

typedef unsigned int uint;

char **table = NULL;

int main(int argc, char *argv[])
{
    FILE *setfp = fopen("syslog.txt", "rb");
    FILE *infp = fopen("log.inp", "rb");
    FILE *outfp = fopen("log.out", "wb");

    uint n, i, j;
    fscanf(setfp, "%u", &n);

    table = (char**)calloc(n, sizeof(uint*));
    table[0] = (char*)calloc(MAX_DAYS*n, sizeof(uint));

    FOR(i, 1, n){
        table[i] = table[i-1] + MAX_DAYS;
    }
    FOR(i, 0, n){
        fread(table[i], sizeof(table[i]), MAX_DAYS, setfp);
    }

    FOR(i, 0, n){
        FOR(j, 0, MAX_DAYS){
            printf("%u ", table[i][j]);
        }
        printf("\n");
    }

    fclose(outfp);
    fclose(infp);
    fclose(setfp);
    return EXIT_SUCCESS;
}