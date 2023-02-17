/* Name: Simon Fliegel
MatrNr.: 53043*/
/******************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "administration.h"

char buf[128];

/**************************Utility Functions*************************/
int isValidId(char* s) {
    if (strlen(s) < 0 || strlen(s) > 2) {
        return 0;
    }
    for (int i = 0; i < strlen(s); i++) {
        if (!isdigit(s[i])) {
            return 0;
        }
    }
    return 1;
}

/****************************Sub Menus******************************/
void printMenu() {
    List* articles = getArticles();

    printf("======================================================================================================\n");
    printf("----------------------------- Beleg von Simon Fliegel, Matrikelnr.: 53043 ----------------------------\n");
    printf("-------------------------------- Aufgabe: 4 | Darstellungsform: 1 (GTK+) -----------------------------\n");
    printf("======================================================================================================\n\n");
    printf("Ausgeliehene Medien:\n\n");
    printf("ID |  Typ   Titel                                               Author/Interpret      Ausgeliehen an\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    displayArticles(articles);
}

int addArticles(List* articles) {
    char proceed;
    Article* new;
    do {
        new = createArticleInteractively();
        printf("==========================================================\n");
        printf("Artikel wurde hinzugefügt:\n");
        printArticle(new);
        append(articles, new);
        printf("Weiteren Artikel hinzufügen (j/n)? ");
        fgets(buf, sizeof(buf), stdin);
        proceed = buf[0];
    } while (proceed == 'j');
    saveArticles(articles);
}

int deleteArticles(List* articles) {
    printf("ID des zu löschenden Mediums eingeben: ");
    fgets(buf, 128, stdin);
    if (!isValidId(buf)) {
        printf("Fehler: ID darf nur Ziffern enthalten und hat maximal zwei Stellen");
    }
}

void main() {
    printMenu();
}





