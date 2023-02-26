/* Name: Simon Fliegel
MatrNr.: 53043*/
/***************************************************************************/

#include "circ_dll.h"
#include "article.h"

#define OK 0
#define FAIL 1

/********************************Functions**********************************/

/**
 * Creates list, reads in articles from "./articles.csv" 
 * @return List* to created list
*/
List* getArticles();

/**
 * Writes every article in a given list to "./articles.csv"
 * @param articles pointer to a list of articles
 * @return 0 -> OK, 1 -> FAIL
*/
int saveArticles(List* articles);

/**
 * Removes a given article from a list and frees memory
 * @param articles pointer to a list of articles
 * @param old pointer to the article which should be deleted
 * @return void
*/
void removeArticleFromList(List* articles, Article* old);

/**
 * Prints every article in a given list
 * @param articles pointer to a list of articles
 * @return void
*/
void displayArticles(List* articles);

/**
 * @param articles pointer to a list of articles
 * @return List* pointer to sorted list
*/
List* sortById(List* articles);

/**
 * @param articles pointer to a list of articles
 * @return List* pointer to sorted list
*/
List* sortByMedia(List* articles);

/**
 * @param articles pointer to a list of articles
 * @return List* pointer to sorted list
*/
List* sortByTitle(List* articles);

/**
 * @param articles pointer to a list of articles
 * @return List* pointer to sorted list
*/
List* sortByAuthor(List* articles);

/**
 * @param articles pointer to a list of articles
 * @return List* pointer to sorted list
*/
List* sortByLender(List* articles);

/**
 * Searches through a list of articles by their ID
 * @param articles pointer to a list of articles
 * @param id sought ID
 * @return Article* of matching article or NULL if the ID was not found
*/
Article* searchById(List* articles, int searchId);

/**
 * Searches through a list of articles by their media type
 * @param articles pointer to list of articles
 * @param media sought media type (Buch, CD, DVD)
 * @return List* containing the search results
*/
List* searchByMedia(List* articles, Media media);

/**
 * Searches through a list of articles by their title
 * @param articles pointer to a list of articles
 * @param title sought title string
 * @return List* containing the search results
*/
List* searchByTitle(List* articles, char* title);

/**
 * Searches through a list of articles by their author
 * @param articles pointer to a list of articles
 * @param author sought author string
 * @return List* containing the search results
*/
List* searchByAuthor(List* articles, char* author);

/** Searches through a list of articles by their lender
 * @param articles pointer to a list of articles
 * @param lender sought lender string
 * @return List* containing the search results
*/
List* searchByLender(List* articles, char* lender);