/* Name:
MatrNr.:*/
/***************************************************************************/

#include "circ_dll.h"
#include "article.h"

/********************************Functions**********************************/

List* getArticles();

int addArticles(List* articles);

int removeArticles(List* articles);

int saveArticles(List* articles);

void displayArticles(List* articles);

List* searchById(List* articles, int searchId);

List* searchByMedia(List* articles, Media media);

List* searchByTitle(List* articles, char* title);

List* searchByAuthor(List* articles, char* author);

List* searchByLender(List* articles, char* lender);


