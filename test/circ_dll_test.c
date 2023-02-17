#include <stdlib.h>
#include <stdio.h>
#include "../circ_dll.h"

int compare(const void* d1, const void* d2) {
    printf("cmp\n");
    int v1 = *(int*)d1;
    int v2 = *(int*)d2;

    if (v1 > v2) return 1;
    else if (v1 < v2) return -1;
    else return 0;
}

int main() {
    List* pList = createList();
    int i1=1, i2=2, i3=3, i4=4, i5=5, i6=6, i7=7, i8=8;

    append(pList, &i3);
    append(pList, &i5);
    append(pList, &i2);
    append(pList, &i4);
    append(pList, &i5);
    append(pList, &i1);

    sortList(pList, compare);
    
    for (int* a = (int*)getFirst(pList); a; a = (int*)getNext(pList)) {
        printf("%d\n", *a);
    }
}