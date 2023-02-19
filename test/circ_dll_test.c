#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../circ_dll.h"

int compare(const void* d1, const void* d2) {
    int v1 = *(int*)d1;
    int v2 = *(int*)d2;

    if (v1 > v2) return 1;
    else if (v1 < v2) return -1;
    else return 0;
}

int compareString(const void* str1, const void* str2) {
    return strcmp((char*)str1, (char*)str2);
}

int main() {
    List* pList = createList();
    List* pSorted;
    char* strs[5] = {"Dumbledore", "Bellatrix", "Dobby", "Ron", "Hermine"};
    int len = sizeof(strs) / sizeof(strs[0]);
    for (int i = 0; i < len; i++) {
        append(pList, strs[i]);
    }

    pSorted = sortList(pList, compareString);
    
    for (char* a = (char*)getFirst(pSorted); a; a = (char*)getNext(pSorted)) {
        printf("%s\n", a);
    }
}