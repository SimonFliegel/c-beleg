/* Name: Simon Fliegel
MatrNr.: 53043*/
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
int compareId(const void* a1, const void* a2) {
    int id1 = getId((Article*)a1);
    int id2 = getId((Article*)a2);
    if (id1 > id2) return 1;
    else if (id1 < id2) return -1;
    else return 0;
}

// private
int compareMedia(const void* a1, const void* a2) {
    int med1 = getMedia((Article*)a1);
    int med2 = getMedia((Article*)a2);
    if (med1 > med2) return 1;
    else if (med1 < med2) return -1;
    else return 0;
}

// private
int compareTitle(const void* a1, const void* a2) {
    return strcmp(getTitle((Article*)a1), getTitle((Article*)a2));
}

// private
int compareAuthor(const void* a1, const void* a2) {
    char* auth1 = getAuthor((Article*)a1);
    char* auth2 = getAuthor((Article*)a2);
    if (auth1 == NULL && auth2 == NULL) return 0;
    else if (auth1 == NULL) return 1;
    else if (auth2 == NULL) return -1;
    else return strcmp(auth1, auth2);
}

// private
int compareLender(const void* a1, const void* a2) {
    return strcmp(getLender((Article*)a1), getLender((Article*)a2));
}

// private
List* searchByString(List* articles, Category cat, char* searchString) {
    char* articleString;
    List* results = createList();
    if (results == NULL) {
        printf("ERROR::%d::%s: creating search results list\n", __LINE__, __FILE__);
        return results;
    }

    processString(&searchString);
    for (Article* curr = (Article*)getFirst(articles); curr; curr = (Article*)getNext(articles)) {
        curr = getCurrent(articles);
        switch (cat) {
            case Title: articleString = getTitle(curr); break;
            case Author: articleString = getAuthor(curr); break;
            case Lender: articleString = getLender(curr); break;
            default : {
                printf("ERROR::%d::%s: wrong category\n", __LINE__, __FILE__);
                return NULL;
            }
        }
        if (articleString == NULL) {
            // when author is null
            continue;
        }
        processString(&articleString);
        // returns null if articleString does not contain searchString
        if (strstr(articleString, searchString)) {
            append(results, curr);
        }
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

void displayArticles(List* articles) {
    for (Article* a = (Article*)getFirst(articles); a; a = (Article*)getNext(articles)) {
        printArticle(a);
    }
}

List* sortById(List* articles) {
    return sortList(articles, compareId);
}

List* sortByMedia(List* articles) {
    return sortList(articles, compareMedia);
}

List* sortByTitle(List* articles) {
    return sortList(articles, compareTitle);
}

List* sortByAuthor(List* articles) {
    return sortList(articles, compareAuthor);
}

List* sortByLender(List* articles) {
    return sortList(articles, compareLender);
}

Article* searchById(List* articles, int id) {
    Article* result = malloc(sizeof(Article));
    if (result == NULL) {
        printf("ERROR::%d::%s: creating search result article\n", __LINE__, __FILE__);
    }

    for(Article* result = (Article*)getFirst(articles); result; result = (Article*)getNext(articles)) {
        if (result->id == id) {
            return result;
        }
    }
    printf("Es konnte kein Artikel zur gesuchten ID %d gefunden werden\n", id);
    return NULL;
}

List* searchByMedia(List* articles, Media media) {
    List* results = createList();
    if (results == NULL) {
        printf("ERROR::%d::%s: creating list\n", __LINE__, __FILE__);
    }

    for(Article* curr = (Article*)getFirst(articles); curr; curr = (Article*)getNext(articles)) {
        if (media == getMedia(curr)) {
            append(results, curr);
        }
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

int saveArticles(List* articles) {
    FILE* pf;
    int ret;

    pf = fopen("data/articles.csv", "wt");
    if (pf == NULL) {
        perror("Error");
        return FAIL;
    }
    
    for (Article* curr = (Article*)getFirst(articles); curr; curr = (Article*)getNext(articles)) {
        ret = writeArticle(pf, curr);
        if (ret) {
            printf("ERROR::%d::%s: writing article to file\n", __LINE__, __FILE__);
            fclose(pf);
            return FAIL;
        }
    }
    
    fclose(pf);
    return OK;
}

void removeArticleFromList(List* articles, Article* old) {
    for (Article* a = (Article*)getFirst(articles); a; a = (Article*)getNext(articles)) {
        if (a == old) {
            removeCurrent(articles);
            deleteArticle(old);
        }
    }
}