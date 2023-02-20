#include <stdlib.h>
#include <stdio.h>

int* getUsedIds() {
    FILE* pf;
    int* usedIds = NULL;
    int* tmp;
    int n;

    pf = fopen("data/id.csv", "rt");
    if (pf == NULL) {
        perror("Error");
        return -1;
    }

    usedIds = malloc(sizeof(int));
    if (usedIds == NULL) {
        printf("ERROR::%s::%d: allocating memory\n", __FILE__, __LINE__);
        return -1;
    }
    for (n = 0; fscanf(pf, "%d,%*[^\n]", usedIds+n) != EOF; n++) {
        tmp = realloc(usedIds, (n+1)*sizeof(int));
        if (tmp == NULL) {
            printf("ERROR::%s::%d: reallocating memory\n", __FILE__, __LINE__);
            return -1;
        }
        usedIds = tmp;
        printf("usedIds[%d]: %d\n", n, usedIds[n]);
    }
    
    return usedIds;
}