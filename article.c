/* Name: Simon Fliegel
MatrNr.: 53043*/

/**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "article.h"

/************************ FUNCTIONS ***************************/

const char* mediaNames[3] = {"Buch", "CD", "DVD"};
static int counter;
char buf[128];

Article* createArticle(Media media, char* title, char* author, char* lender) {
    if (title && lender) {
        Article* a = malloc(sizeof(Article));
        if (a) {
            a->media = media;
            a->title = title;
            a->author = author;
            a->lender = lender;
            a->id = counter++;
            return a;
        } else {
            printf("ERROR::%d::%s: creating article\n", __LINE__, __FILE__);
        }
    } else {
        printf("ERROR::%d::%s: title and lender can't be NULL\n", __LINE__, __FILE__);
    }
    return NULL;
}

Article* createArticleInteractively() {
    Article* a = malloc(sizeof(Article));
    if (a == NULL) {
        printf("ERROR::%d::%s: creating article\n", __LINE__, __FILE__);
        return NULL;
    }
    // media type
    printf("ausgeliehenes Medium ('b'-Buch / 'c'-CD / 'd'-DVD): ");
    fgets(buf, sizeof(buf), stdin);
    if (strlen(buf)-1 != 1) {
        printf("FEHLER: unerwartete Eingabe ('b' / 'c' / 'd')\n");
        free(a);
        return NULL;
    }
    switch(buf[0]) {
        case 'b': a->media = Buch; break;
        case 'c': a->media = Cd; break;
        case 'd': a->media = Dvd; break;
        default: {
            printf("FEHLER: Eingabe muss entweder 'b'=Buch, 'c'=CD, 'd'=DVD entsprechen\n");
            free(a);
            return NULL;
        }
    }
    // title
    printf("Titel: ");
    fgets(buf, sizeof(buf), stdin);
    if (strlen(buf)-1 == 0) {
        printf("FEHLER: Titel muss mindestens ein Zeichen enthalten\n");
        free(a);
        return NULL;
    }
    buf[strlen(buf)-1] = '\0';
    a->title = malloc((strlen(buf)+1));
    if (a->title) {
        strcpy(a->title, buf);
    } else {
        printf("ERROR::%d::%s: allocating title\n", __LINE__, __FILE__);
        free(a);
        return NULL;
    }
    // author
    printf("Autor/ Interpret (wenn vorhanden): ");
    fgets(buf, sizeof(buf), stdin);
    buf[strlen(buf)-1] = '\0';
    if (strlen(buf)) { // not empty
        a->author = malloc((strlen(buf)+1));
        if (a->author) {
            strcpy(a->author, buf);
        } else {
            printf("ERROR::%d::%s: allocating author\n", __LINE__, __FILE__);
            free(a);
            return NULL;
        }
    } else { // empty
        a->author = NULL;
    }
    // lender
    printf("ausleihende Person: ");
    fgets(buf, sizeof(buf), stdin);
    if (strlen(buf)-1 == 0) {
        printf("FEHLER: Name der ausleihenden Person muss mindestens ein Zeichen enthalten\n");
        free(a);
        return NULL;
    }
    buf[strlen(buf)-1] = '\0';
    a->lender = malloc((strlen(buf)+1));
    if (a->lender) {
        strcpy(a->lender, buf);
    } else {
        printf("ERROR::%d::%s: allocating lender\n", __LINE__, __FILE__);
        free(a);
        return NULL;
    }
    a->id = counter++;
    return a;
}

int getId(Article* a) {
    if (a == NULL) {
        printf("ERROR::%d::%s: article was null\n", __LINE__, __FILE__);
        return -1;
    }
    return a->id;
}

int getMedia(Article* a) {
    if (a == NULL) {
        printf("ERROR::%d::%s: article was null\n", __LINE__, __FILE__);
        return -1;
    }
    return a->media;
}

char* getTitle(Article* a) {
    if (a == NULL) {
        printf("ERROR::%d::%s: article was null\n", __LINE__, __FILE__);
        return NULL;
    }
    return a->title;
}

char* getAuthor(Article* a) {
    if (a == NULL) {
        printf("ERROR::%d::%s: article was null\n", __LINE__, __FILE__);
        return NULL;
    }
    return a->author;
}

char* getLender(Article* a) {
    if (a == NULL) {
        printf("ERROR::%d::%s: article was null\n", __LINE__, __FILE__);
        return NULL;
    }
    return a->lender;
}

void printArticle(Article* a) {
    if (a) {
        printf("%-2d |  %-4s  %-50s  %-20s  %-20s\n", a->id, mediaNames[a->media], a->title, a->author ? a->author : "", a->lender);
    } else {
        printf("ERROR::%d::%s: article was NULL\n", __LINE__, __FILE__);
    }
}

int writeArticle(FILE* pf, Article* a) {
    if (a) {
        fprintf(pf, "%d,%d,%s,%s,%s\n", a->id, a->media, a->title, a->author == NULL ? "-1" : a->author, a->lender);
        return OK;
    } else {
        printf("ERROR::%d::%s: article was NULL\n", __LINE__, __FILE__);
        return FAIL;
    }
}

Article* readArticle(FILE* pf) {
    int ret;
    char tmpTitle[128], tmpAuthor[128], tmpLender[128];
    Article* a = malloc(sizeof(Article));
    if (a) {
        ret = fscanf(pf, "%d,%d,%[^,],%[^,],%[^,\n]", &(a->id), (int*)&(a->media), tmpTitle, tmpAuthor, tmpLender);
        if (ret <= 0) {
            free(a);
            return NULL;
        }
        // title
        a->title = malloc(strlen(tmpTitle)+1);
        if (a->title) {
            strcpy(a->title, tmpTitle);
        } else {
            printf("ERROR::%d::%s: allocating title\n", __LINE__, __FILE__);
            free(a);
            return NULL;
        }
        // author
        if (strcmp(tmpAuthor, "-1\0")) {
            a->author = malloc(strlen(tmpAuthor)+1);
            if (a->author) {
                strcpy(a->author, tmpAuthor);
            } else {
                printf("ERROR::%d::%s: allocating author\n", __LINE__, __FILE__);
                free(a);
                return NULL;
            }
        } else {
            a->author = NULL;
        }
        // lender
        a->lender = malloc(strlen(tmpLender)+1);
        if (a->lender) {
            strcpy(a->lender, tmpLender);
        } else {
            printf("ERROR::%d::%s: allocating lender\n", __LINE__, __FILE__);
            free(a);
            return NULL;
        }       
    } else {
        printf("ERROR::%d::%s: creating article\n", __LINE__, __FILE__);
        free(a);
        return NULL;
    }
    return a;
}

void deleteArticle(Article* a) {
    free(a);
}

