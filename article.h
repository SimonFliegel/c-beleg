/* Name: Simon Fliegel
MatrNr.: 53043*/

/********************************************************************/

#include <stdio.h>

#define OK 0
#define FAIL 1

typedef enum media{
    Buch, // = 0
    Cd,   // = 1
    Dvd,  // = 2
} Media;

typedef struct article{
    int id;
    Media media;
    char* title;
    char* author;
    char* lender;
} Article;


/******************************Functions*****************************/

/**
 * @param media enum media {Buch=0, Cd=1, Dvd=2}
 * @param title char*
 * @param author char* or NULL
 * @param lender char*
 * @return pointer to struct article
 * 
*/
Article* createArticle(Media media, char* title, char* author, char* lender);

/**
 * Creates an article via console dialog.
 * @return pointer to struct article
*/
Article* createArticleInteractively();

/**
 * @param pArticle pointer to a struct article
 * @return ID of a given Article
*/
int getId(Article* pArticle);

/**
 * @param pArticle pointer to a struct article
 * @return media-type (int) of a given Article
*/
int getMedia(Article* pArticle);

/**
 * @param pArticle pointer to a struct article
 * @return title string of a given Article
*/
char* getTitle(Article* pArticle);

/**
 * @param pArticle pointer to a struct article
 * @return author string of a given Article
*/
char* getAuthor(Article* pArticle);

/**
 * @param pArticle pointer to a struct article
 * @return lender string of a given Article
*/
char* getLender(Article* pArticle);

/**
 * Prints a given article to the console.
 * @param pArticle pointer to struct article
 * @return void
*/
void printArticle(Article* pArticle);

/**
 * Writes given article to ./articles.csv. In case of NULL '-1' is written.
 * @param pf pointer to a stream
 * @param pArticle pointer to a struct article
 * @return 0 = OK, 1 = FAIL
*/
int writeArticle(FILE* pf, Article* pArticle);

/**
 * Reads articles from ./articles.csv
 * @param pf pointer to a stream
 * @return pointer to struct article
*/
Article* readArticle(FILE* pf);

/**
 * @param pointer to struct Article
 * @return void
*/
void deleteArticle(Article* pArticle);