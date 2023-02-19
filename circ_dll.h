/* Name: Simon Fliegel
MatrNr.: 53043*/

/**********************************************************/

#define OK 0
#define FAIL 1

struct list;
typedef struct list List;

/**
 * Inizializes list and creates head node containing:
 * - next-pointer to first node
 * - previous-pointer to last node
 * - current-pointer to current node
 * Next- and previous-pointer are both initially pointing
 * to the list itself. Current-pointer is initially NULL.                             
 * @return List* to created List
*/
List* createList();

/**
 * @param pList pointer to list
 * @return void
*/
void deleteList(List* pList);

/**
 * Inserts new node after the current node and sets current node to newly inserted node
 * @param pList pointer to list
 * @param pNewData void* to data which should be inserted
 * @return 0 -> OK, 1 -> FAIL
 * 
*/
int insertAfter(List* pList, void* pNewData);

/**
 * Inserts new node at the end and sets current node to newly inserted node
 * @param pList pointer to list
 * @param pNewData void* to data to be inserted
 * @return 0 -> OK, 1 -> FAIL
*/
int append(List* pList, void* pNewData);

/**
 * Inserts new node at the front and sets current node to newly inserted node
 * @param pList pointer to list
 * @param pNewData void* to data to be inserted
 * @return 0 -> OK, 1 -> FAIL
*/
int push(List* pList, void* pNewData);

/**
 * Removes current node and sets current node to the previous node
 * @param pList pointer to list
 * @param pNewData void* to data to be inserted
 * @return 0 -> OK, 1 -> FAIL
*/
int removeCurrent(List* pList);

/**
 * Removes last node and sets current node to the new last node
 * @param pList pointer to list
 * @return 0 -> OK, 1 -> FAIL
*/
int removeLast(List* pList);

/**
 * Removes first node and sets current node to the new first node
 * @param pList pointer to list
 * @return 0 -> OK, 1 -> FAIL
*/
int removeFirst(List* pList);

/**
 * @param pList pointer to list
 * @return void* to data of current node
*/
void* getCurrent(List* pList);

/**
 * Returns first node and sets current pointer to it
 * @param pList pointer to list
 * @return void* to data of first node
*/
void* getFirst(List* pList);

/**
 * Returns last node and sets current pointer to it
 * @param pList pointer to list
 * @return void* to data of last node
*/
void* getLast(List* pList);

/**
 * Returns next node and sets current pointer to it
 * @param pList pointer to list
 * @return void* to data of next node
*/
void* getNext(List* pList);

/**
 * @param pList pointer to list
 * @return 1 - true, 0 - false
*/
int isEmpty(List* pList);

/**
 * @param pList pointer to list
 * @return int length (head not included)
*/
int getLength(List* pList);

/**
 * Returns node of given index (head not included in indexing)
 * @param pList pointer to list
 * @param index
 * @return void* to data of indexed node
 * @exception index out of bounds -> NULL
*/
void* getIndexed(List* pList, int index);

/**
 * Sorts list by a certain criteria passed by compare-method
 * @param pList pointer to list
 * @param compare function pointer to a method of type int(*compare)(const void*, const void*)
 * which returns negative value if first value is smaller, positive value if it is greater and 0 if they are equal
 * @return pointer to a sorted List
*/
List* sortList(List* pList, int (*compare)(const void*, const void*));

/**
 * Creates the copy of a given list
 * @param pList pointer to list
 * @return List* pointer to the copy
*/
List* copyList(List* pList);