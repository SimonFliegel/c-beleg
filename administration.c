/* Name:
MatrNr.:*/
/****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "circ_dll.h"
#include "article.h"

/**************************Utility Functions*********************************/
// private
List* searchByString(char* searchString);
// private
List* searchByInt(int searchVal);

/*****************************Functions**************************************/

List* getArticles() {
    Article* a;
    List* articles = createList();
    if (articles == NULL) {
        printf("ERROR::%d::%s: creating article list\n", __LINE__, __FILE__);
        return articles;
    }
    FILE* pf = fopen("data/articles.csv", "rt");
    if (pf) {
        while ((a = readArticle(pf)) != NULL) {
            append(articles, &a);
        }
        fclose(pf);
    } else {
        perror("Error");
        deleteList(articles);
    }
    return articles;
}

void displayArticles(List* articles) {
    setCurrentToHead(articles);
    while (hasNext(articles)) {
        printArticle((Article*)getNext(articles));
    }
}

List* searchById(int id) {
    //do sth.
}