/* Name:
MatrNr.:*/
/******************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "article.h"
#include "circ_dll.h"

/**************************Utility Functions*************************/

int addArticles(List* articles) {
    char buf[128];
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
}

int isValidId(char* s) {
    if (strlen(s) < 0 || strlen(s) >= 3) {
        return 0;
    }
    for (int i = 0; i < strlen(s); i++) {
        if (!isdigit(s[i])) {
            return 0;
        }
    }
    return 1;
}