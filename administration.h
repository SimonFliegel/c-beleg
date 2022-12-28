/* Name:
MatrNr.:*/
/***************************************************************************/

#include "circ_dll.h"
#include "article.h"

#define OK 1
#define FAIL 0

/********************************Functions**********************************/

List* getArticles();

int saveArticles(List* articles);

void displayArticles(List* articles);

Article* searchById(List* articles, int searchId);

List* searchByMedia(List* articles, Media media);

List* searchByTitle(List* articles, char* title);

List* searchByAuthor(List* articles, char* author);

List* searchByLender(List* articles, char* lender);

int isValidId(char* s);


