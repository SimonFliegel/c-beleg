/* Name:
MatrNr.: */

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

// Repeat instead of cancellation?
Article* createArticleInteractively() {
    Article* a = malloc(sizeof(Article));
    if (a) {
        // media type
        printf("ausgeliehenes Medium ('b'-Buch / 'c'-CD / 'd'-DVD): ");
        fgets(buf, sizeof(buf), stdin);
        if (strlen(buf)-1 != 1) {
            printf("FEHLER: unerwartete Eingabe ('b' / 'c' / 'd')\nAbbruch...\n");
            free(a);
            return NULL;
        }
        switch(buf[0]) {
            case 'b': a->media = Buch; break;
            case 'c': a->media = Cd; break;
            case 'd': a->media = Dvd; break;
            default: {
                printf("FEHLER: Eingabe muss entweder 'b'=Buch, 'c'=CD, 'd'=DVD entsprechen\nAbbruch...\n");
                free(a);
                return NULL;
            }
        }
        // title
        printf("Titel: ");
        fgets(buf, sizeof(buf), stdin);
        if (strlen(buf)-1 == 0) {
            printf("FEHLER: Titel muss mindestens ein Zeichen enthalten\nAbbruch...\n");
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
        a->author = malloc((strlen(buf)+1));
        if (a->author) {
            strcpy(a->author, buf);
        } else {
            printf("ERROR::%d::%s: allocating author\n", __LINE__, __FILE__);
            free(a);
            return NULL;
        }
        // lender
        printf("ausleihende Person: ");
        fgets(buf, sizeof(buf), stdin);
        if (strlen(buf)-1 == 0) {
            printf("FEHLER: Name der ausleihenden Person muss mindestens ein Zeichen enthalten\nAbbruch...\n");
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
    } else {
        printf("ERROR::%d::%s: creating article\n", __LINE__, __FILE__);
    }
    a->id = counter++;
    return a;
}

void printArticle(Article* a) {
    if (a) {
        printf("%-3d, %-4s, %-30s, %-20s, %-20s\n", a->id, mediaNames[a->media], a->title, a->author, a->lender);
    } else {
        printf("ERROR::%d::%s: article was NULL\n", __LINE__, __FILE__);
    }
}

int writeArticle(FILE* pf, Article* a) {
    if (a) {
        return fprintf(pf, "%d,%d,%s,%s,%s\n", a->id, a->media, a->title, a->author == NULL ? "-1" : a->author, a->lender);
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
            printf("FEHLER::%d::%s: Es konnte nichts eingelesen werden\n", __LINE__, __FILE__);
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
            printf("author ist nicht null\n");
            printf("%c\n", tmpAuthor[0]);
            a->author = malloc(strlen(tmpAuthor)+1);
            if (a->author) {
                strcpy(a->author, tmpAuthor);
            } else {
                printf("ERROR::%d::%s: allocating author\n", __LINE__, __FILE__);
                free(a);
                return NULL;
            }
        } else {
            printf("author ist null\n");
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
    // does it catch everything?
    free(a);
}

