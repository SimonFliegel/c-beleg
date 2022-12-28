/* Name:
MatrNr.:*/
/****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "circ_dll.h"
#include "article.h"

typedef enum category {
    Title,
    Author,
    Lender,
} Category;

/**************************Utility Functions*********************************/

// private
void processString(char** s) {
    int count = 0;
    char* tmp = malloc(strlen(*s));
    strcpy(tmp, *s);
    for (int i = 0; tmp[i]; i++) {
        tmp[i] = tolower(tmp[i]);
        if (tmp[i] != ' ') {
            tmp[count++] = tmp[i];
        }
    }
    tmp[count] = '\0';
    *s = tmp;
}

// private
List* searchByString(List* articles, Category cat, char* searchString) {
    Article* current;
    char* articleString;
    List* results = createList();
    if (results == NULL) {
        printf("ERROR::%d::%s: creating search results list\n", __LINE__, __FILE__);
        return results;
    }

    processString(&searchString);
    setCurrentToFirst(articles);
    while (getCurrent(articles)) {
        current = getCurrent(articles);
        switch (cat) {
            case Title: articleString = getTitle(current); break;
            case Author: articleString = getAuthor(current); break;
            case Lender: articleString = getLender(current); break;
            default : {
                printf("ERROR::%d::%s: wrong category\n", __LINE__, __FILE__);
                return NULL;
            }
        }
        processString(&articleString);
        // returns null if articleString does not contain searchString
        if (strstr(articleString, searchString)) {
            append(results, current);
        }
        getNext(articles);
    }
    return results;
}

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
            append(articles, a);
        }
        fclose(pf);
    } else {
        perror("Error");
        deleteList(articles);
    }
    return articles;
}

// doesn't print last article -> DEBUG
void displayArticles(List* articles) {
    setCurrentToFirst(articles);
    while (getCurrent(articles)) {
        printArticle((Article*)getCurrent(articles));
        getNext(articles);
    }
}

Article* searchById(List* articles, int id) {
    Article* result = malloc(sizeof(Article));
    if (result == NULL) {
        printf("ERROR::%d::%s: creating search result article\n", __LINE__, __FILE__);
    }
    setCurrentToFirst(articles);
    while (getCurrent(articles)) {
        result = (Article*)getCurrent(articles);
        if (result->id == id) {
            return result;
        }
        getNext(articles);
    }
    printf("Es konnte kein Artikel zur gesuchten ID %d gefunden werden\n", id);
    return NULL;
}

List* searchByMedia(List* articles, Media media) {
    Article* current;
    List* results = createList();
    if (results == NULL) {
        printf("ERROR::%d::%s: creating list\n", __LINE__, __FILE__);
    }

    setCurrentToFirst(articles);
    while (hasCurrent(articles)) {
        current = getCurrent(articles);
        if (media == getMedia(current)) {
            append(results, current);
        }
        getNext(articles);
    }
    return results;
}

List* searchByTitle(List* articles, char* title) {
    return searchByString(articles, Title, title);
}

List* searchByAuthor(List* articles, char* author) {
    return searchByString(articles, Author, author);
}

List* searchByLender(List* articles, char* lender) {
    return searchByString(articles, Lender, lender);
}

// TODO saveArticles