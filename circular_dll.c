/* Simon Fliegel
MatrNr. 53043*/
/*-----------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "circular_dll.h";

typedef struct Node {
    void* pData;
    Node* pNext;
    Node* pPrev;
} Node;

// head
typedef struct List{
    Node head; // data=NULL, next=tail, prev=head
    Node* pCurr;
} List;

int insertBehindNode(List* pList, Node* pPrev, void* pNewData) {
    if (pPrev) {
        Node* pNode = malloc(sizeof(Node));
        if (pNode) {
            pNode->pData = pNewData;
            pNode->pNext = pPrev->pNext;
            pNode->pPrev = pPrev;
            // setting next-pointer of previous element
            if (pPrev->pNext == NULL) { // Wenn am Ende der Liste eingefügt wird...
                pList->head.pNext
            }
            pPrev->pNext = pNode;
            // setting previous-pointer of next element
            pNode->pNext->pPrev = pNode;
            return OK;
        }
    }
    return FAIL;
}

int removeNode(List* pList, Node* pNode) {
    if (pNode) {
        pNode->pPrev->pNext = pNode->pNext;
        pNode->pNext->pPrev = pNode->pPrev;
        free(pNode);
        return OK;
    }
    return FAIL;
}

List* createList() {
    List* pList = malloc(sizeof(List));
    if (pList) {
        pList->head.pNext = (Node*)pList; // initialized pointing to itself
        pList->head.pPrev = (Node*)pList;
        pList->pCurr = NULL;
    } 
    return pList;
}

int insertAfter(List* pList, Node* pPrev, void* pNewData) {
    return insertBehindNode(pList, pPrev, pNewData);
}

int append(List* pList, void* pNewData) {
    return insertAfter(pList, pList->head.pNext, pNewData);
}





// int deleteList(List* pList) {
//     if (pList) {
//         for (pList->pcurrent = pList->pcurrent->pnext; pList->pcurrent; )

//     }
// }