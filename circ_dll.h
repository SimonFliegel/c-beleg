/* Name:
MatrNr.: */

/**********************************************************/

#define OK 1
#define FAIL 0

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
 * @return 1 -> OK, 0 -> FAIL
 * 
*/
int insertAfter(List* pList, void* pNewData);

/**
 * Inserts new node at the end and sets current node to newly inserted node.
 * @param pList pointer to list
 * @param pNewData void* to data to be inserted
 * @return 1 -> OK, 0 -> FAIL
*/
int append(List* pList, void* pNewData);

/**
 * Inserts new node at the front and sets current node to newly inserted node.
 * @param pList pointer to list
 * @param pNewData void* to data to be inserted
 * @return 1 -> OK, 0 -> FAIL
*/
int push(List* pList, void* pNewData);

/**
 * Removes current node and sets current node to the previous node.
 * @param pList pointer to list
 * @param pNewData void* to data to be inserted
 * @return 1 -> OK, 0 -> FAIL
*/
int removeCurrent(List* pList);

/**
 * Removes last node and sets current node to the new last node.
 * @param pList pointer to list
 * @return 1 -> OK, 0 -> FAIL
*/
int removeLast(List* pList);

/**
 * Removes first node and sets current node to the new first node.
 * @param pList pointer to list
 * @return 1 -> OK, 0 -> FAIL
*/
int removeFirst(List* pList);

/**
 * Sets current node to first node.
 * @param pList pointer to list
 * @return void
*/
void setCurrentToHead(List* pList);

/**
 * @param pList pointer to list
 * @return void* to data of current node
*/
void* getCurrent(List* pList);

/**
 * Returns first node and sets current pointer to it.
 * @param pList pointer to list
 * @return void* to data of first node
*/
void* getFirst(List* pList);

/**
 * Returns last node and sets current pointer to it.
 * @param pList pointer to list
 * @return void* to data of last node
*/
void* getLast(List* pList);

/**
 * Returns next node and sets current pointer to it.
 * @param pList pointer to list
 * @return void* to data of next node
*/
void* getNext(List* pList);

/**
 * @param pList pointer to list
 * @return 1 - true, 0 - false 
*/
int hasNext(List* pList);

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
 * Returns node of given index (head not included in indexing).
 * @param pList pointer to list
 * @param index
 * @return void* to data of indexed node
 * @exception index out of bounds -> NULL
*/
void* getIndexed(List* pList, int index);
