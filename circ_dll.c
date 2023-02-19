/* Name: Simon Fliegel
MatrNr.: 53043*/

/*****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "circ_dll.h"

typedef struct node {
    void* pData;
    struct node* pNext;
    struct node* pPrev;
} Node;

typedef struct list{
    Node head; // data=NULL, next=first, prev=last
    Node* pCurr;
} List;

/********************* HELPER FUNCTIONS ***********************/

// private
int insertBehindNode(List* pList, Node* pPrev, void* pNewData) {
    if (pPrev && pNewData) {
        Node* pNode = malloc(sizeof(Node));
        if (pNode) {
            // configure node to be inserted
            pNode->pData = pNewData;
            pNode->pNext = pPrev->pNext;
            pNode->pPrev = pPrev;
            // set next-pointer of previous element
            pPrev->pNext = pNode;
            // set previous-pointer of next element
            pNode->pNext->pPrev = pNode;
            // set current-pointer to inserted node
            pList->pCurr = pNode;
            
            return OK;
        }
    }
    return FAIL;
}

// private
int removeNode(Node* pNode) {
    if (pNode) {
        pNode->pPrev->pNext = pNode->pNext;
        pNode->pNext->pPrev = pNode->pPrev;
        free(pNode);
        return OK;
    }
    return FAIL;
}

List* copyList(List* pList) {
    List* copy = malloc(sizeof(List));
    if (copy) {
        // initial setup
        copy->head.pNext = (Node*)copy;
        copy->head.pPrev = (Node*)copy;
        copy->head.pData = NULL;
        copy->pCurr = NULL;
        // copying data
        pList->pCurr = pList->head.pNext;
        while(pList->pCurr->pData) {
            insertBehindNode(copy, copy->head.pPrev, pList->pCurr->pData);
            pList->pCurr = pList->pCurr->pNext;
        }
    }
    return copy;
}

int isEmpty(List* pList) {
    if (pList->head.pNext == (Node*)pList) {
        return 1;
    }
    return 0;
}

/************************ FUNCTIONS **************************/

List* createList() {
    List* pList = malloc(sizeof(List));
    if (pList) {
        pList->head.pNext = (Node*)pList; // initialized pointing to itself
        pList->head.pPrev = (Node*)pList;
        pList->head.pData = NULL; // identification of head
        pList->pCurr = NULL;
    } 
    return pList;
}

int insertAfter(List* pList, void* pNewData) {
    return insertBehindNode(pList, pList->pCurr, pNewData);
}

int append(List* pList, void* pNewData) {
    return insertBehindNode(pList, pList->head.pPrev, pNewData);
}

int push(List* pList, void* pNewData) {
    return insertBehindNode(pList, &pList->head, pNewData);
}

int removeCurrent(List* pList) {
    pList->pCurr = pList->pCurr->pPrev;
    return removeNode(pList->pCurr->pNext);
}

int removeLast(List* pList) {
    pList->pCurr = pList->head.pPrev->pPrev;
    return removeNode(pList->head.pPrev);
}

int removeFirst(List* pList) {
    pList->pCurr = pList->head.pNext->pNext;
    return removeNode(pList->head.pNext);
}

void* getCurrent(List* pList) {
    if (pList->pCurr == NULL) {
        printf("ERROR::%d::%s: pCurr==NULL\n", __LINE__, __FILE__);
        return NULL;
    }
    return pList->pCurr->pData;
}

void* getFirst(List* pList) {
    if (isEmpty(pList)) {
        return NULL;
    }
    pList->pCurr = pList->head.pNext;
    return pList->pCurr->pData;
}

void* getLast(List* pList) {
    if (isEmpty(pList)) {
        printf("ERROR::%d::%s: list is empty\n", __LINE__, __FILE__);
        return NULL;
    }
    pList->pCurr = pList->head.pPrev;
    return pList->pCurr->pData;
}

void* getNext(List* pList) {
    if (pList->pCurr == NULL) {
        printf("ERROR::%d::%s: pCurr==NULL\n", __LINE__, __FILE__);
        return NULL;
    }
    pList->pCurr = pList->pCurr->pNext;
    return pList->pCurr->pData;
}

// head not included in indexing
void* getIndexed(List* pList, int index) {
    if (isEmpty(pList)) {
        printf("ERROR::%d::%s: list is empty\n", __LINE__, __FILE__);
        return NULL;
    }
    pList->pCurr = pList->head.pNext;
    for (int i = 1; i <= index; i++) {
        pList->pCurr = pList->pCurr->pNext;
        if (pList->pCurr->pData == NULL) {
            printf("ERROR::%d::%s: index out of bounds\n", __LINE__, __FILE__);
            return NULL;
        }
    }
    return pList->pCurr->pData;
}

int getLength(List* pList) {
    Node* pTmpCurr = pList->pCurr; 
    int n = 0;
    if (isEmpty(pList)) {
        return 0;
    }
    pList->pCurr = pList->head.pNext;
    while (pList->pCurr->pData) {
        n++;
        pList->pCurr = pList->pCurr->pNext;
    }
    pList->pCurr = pTmpCurr;
    return n;
}

List* sortList(List* pList, int (*compare)(const void*, const void*)) {
    if (isEmpty(pList)) {
        printf("ERROR::%d::%s: list is empty\n", __LINE__, __FILE__);
        return NULL;
    }
    List* pSorted = copyList(pList);
    Node* curr = pSorted->head.pNext;
    Node* index;
    void* tmp;

    while (curr->pNext->pData) {
        index = curr->pNext;
        while (index->pData) {
            if (compare(curr->pData, index->pData) > 0) {
                tmp = curr->pData;
                curr->pData = index->pData;
                index->pData = tmp;
            }
            index = index->pNext;
        }
        curr = curr->pNext;
    }
    return pSorted;
}

void deleteList(List* pList) {
    if (pList) {
        pList->pCurr = pList->head.pNext;
        while (pList->pCurr->pData) {
            pList->pCurr = pList->pCurr->pNext;
            removeNode(pList->pCurr->pPrev);
        }
    }
    free(pList);
}

