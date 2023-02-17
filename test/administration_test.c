#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "administration.h"

int main() {
    FILE* pf;
    Article* a;
    List* articles = getArticles();
    List* results;
    Article* result;

    a = createArticleInteractively();

    append(articles, a);

    saveArticles(articles);

    deleteList(articles);

    printf("=========================================\n");

    articles = getArticles();
    
    displayArticles(articles);

    printf("=================================================\n");

    result = searchById(articles, 0);

    printArticle(result);
    
    exit(0);
}