/* Name: Simon Fliegel
MatrNr.: 53043*/
/******************************************************************/

#define WIDTH 102
#define SEPARATOR "--------------------------------------------------------------------------------------------------------------\
-------------------------------------------------------------------------------------------------------"
#define BOLD_SEPARATOR "=========================================================================================================\
======================================================================================================="

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

/***********************Formatting Functions*************************/
void printSeparator(char* str, int isBold) {
    int len, remainder, left_offset, right_offset;
    len = strlen(str);
    remainder = WIDTH - len;
    left_offset = remainder / 2;
    if (remainder % 2 != 0) {
        right_offset = remainder / 2 + 1;
    } else {
        right_offset = remainder / 2;
    }
    printf("%.*s%s%.*s\n", left_offset, isBold ? BOLD_SEPARATOR : SEPARATOR, 
        str, right_offset, isBold ? BOLD_SEPARATOR : SEPARATOR);
}

void printArticleHeader() {
    printf("ID |  Typ   Titel                                               Autor/Interpret      Ausgeliehen an\n");
}

void printResult(Article* a, char* header) {
    printSeparator(header, 0);
    printArticleHeader();
    printSeparator("", 0);
    printArticle(a);
}

void printResults(List* results, char* header) {
    printSeparator(header, 0);
    printArticleHeader();
    printSeparator("", 0);
    displayArticles(results);
}

/*************************Search Sub Menus*************************+*/
void searchByIdMenu() {
    int id;
    Article* result;
    List* articles;

    articles = getArticles();
    printf("ID eingeben: ");
    fgets(buf, 128, stdin);
    buf[strlen(buf)-1] = '\0';
    if (!isValidId(buf)) {
        printf("FEHLER: ID darf nur Ziffern enthalten und hat maximal zwei Stellen\n");
        return;
    }
    id = atoi(buf);
    result = searchById(articles, id);
    if (result == NULL) {
        printf("Es konnte kein ausgeliehenes Medium zur gesuchten ID %d gefunden werden\n", id);
        return;
    } 
    printResult(result, " Suchergebnis ");
}

void searchByMediaMenu() {
    char action;
    List* articles;
    List* results;

    articles = getArticles();
    printf("Medienart eingeben ('b'-Buch, 'c'-CD, 'd'-DVD): ");
    fgets(buf, 128, stdin);
    action = buf[0];
    switch(action) {
        case 'b': results = searchByMedia(articles, Buch); break;
        case 'c': results = searchByMedia(articles, Cd); break;
        case 'd': results = searchByMedia(articles, Dvd); break;
        default: printf("FEHLER: Eingabe muss 'b'-Buch, 'c'-CD oder 'd'-DVD entsprechen"); return;
    }
    if (results == NULL) {
        printf("Es konnten keine ausgeliehenen Medien dieser Art gefunden werden\n");
        return;
    }
    printResults(results, " Suchergebnisse ");
}

void searchByTitleMenu() {
    List* articles;
    List* results;

    articles = getArticles();
    printf("Titel eingeben: ");
    fgets(buf, 128, stdin);
    buf[strlen(buf)-1] = '\0';
    results = searchByTitle(articles, buf);
    if (results == NULL) {
        printf("Es konnten keine ausgeliehnen Medien gefunden werden\n");
        return;
    }
    printResults(results, " Suchergebnisse ");
}

void searchByAuthorMenu() {
    List* articles;
    List* results;

    articles = getArticles();
    printf("Autor eingeben: ");
    fgets(buf, 128, stdin);
    buf[strlen(buf)-1] = '\0';
    results = searchByAuthor(articles, buf);
    if (results == NULL) {
        printf("Es konnten keine ausgeliehenen Medien gefunden werden\n");
        return;
    }
    printResults(results, " Suchergebnisse ");
}

void searchByLenderMenu() {
    List* articles;
    List* results;

    articles = getArticles();
    printf("Namen der ausleihenden Person eingeben: ");
    fgets(buf, 128, stdin);
    buf[strlen(buf)-1] = '\0';
    results = searchByLender(articles, buf);
    if (results == NULL) {
        printf("Es konnten keine ausgeliehnen Medien gefunden werden\n");
        return;
    }
    printResults(results, " Suchergebnisse ");
}

/****************************Sub Menus******************************/
// Main Menu
void printMenu() {
    List* articles = getArticles();
    system("clear");
    printSeparator("", 1);
    printSeparator(" Beleg von Simon Fliegel, Matrikelnr.: 53043 ", 0);
    printSeparator(" Aufgabe: 4 | Darstellungsform: 1 (GTK+) ", 0);
    printSeparator("", 1);
    printf("Ausgeliehene Medien:\n\n");
    printArticleHeader();
    printSeparator("", 0);
    displayArticles(articles);
    printf("\n'h' für Hilfe\n");
    printf("'q' zum Verlassen\n");
    printf("\nAktion auswählen: ");
}

void printHelpMenu() {
    printSeparator(" Hilfe ", 1);
    printf("l - Alle ausgeliehenen Medien ausgeben\n");
    printf("a - Medien hinzufügen\n");
    printf("d - Medien entfernen\n");
    printf("s - Medien sortieren\n");
    printf("f - Medien durchsuchen\n");
    printf("\nEingabe zum Verlassen: ");
    fgets(buf, 128, stdin);
}

void sortMenu() {
    char action;
    List* articles;
    List* sortedArticles;

    articles = getArticles();
    printf("\n");
    printSeparator("", 0);
    printf("Sortieren nach...\n");
    printf("i - ID\n");
    printf("m - Medium (Buch, CD, DVD)\n");
    printf("t - Titel\n");
    printf("a - Autor\n");
    printf("l - ausleihende Person\n");
    printf("\nEingabe: ");
    fgets(buf, 128, stdin);
    action = buf[0];
    switch (action) {
        case 'i': case 'I': sortedArticles = sortById(articles);
        case 'm': case 'M': sortedArticles = sortByMedia(articles);
        case 't': case 'T': sortedArticles = sortByTitle(articles);
        case 'a': case 'A': sortedArticles = sortByAuthor(articles);
        case 'l': case 'L': sortedArticles = sortByLender(articles);
    }
    printResults(sortedArticles, " Sortierung ");
    printf("\nEingabe zum Verlassen: ");
    fgets(buf, 128, stdin);
}

void searchMenu() {
    char action;
    List* articles;
    List* copy;
    articles = getArticles();
    printf("\n");
    printSeparator("", 0);
    printf("Durchsuchen nach...\n");
    printf("i - ID\n");
    printf("m - Medium (Buch, CD, DVD)");
    printf("t - Titel\n");
    printf("a - Autor\n");
    printf("l - ausleihende Person\n");
    printf("\nEingabe: ");
    fgets(buf, 128, stdin);
    action = buf[0];
    switch (action) {
        case 'i': case 'I': searchByIdMenu(); break;
        case 'm': case 'M': searchByMediaMenu(); break;      
        case 't': case 'T': searchByTitleMenu(); break;
        case 'a': case 'A': searchByAuthorMenu(); break;
        case 'l': case 'L': searchByLenderMenu(); break;
    }
    printf("\nEingabe zum Verlassen: ");
    fgets(buf, 128, stdin);
}

void displayArticlesMenu() {
    char action;
    char subAction;
    char respond;
    int id;
    Article* result;
    List* articles;
    List* results;
    
    system("clear");
    printSeparator(" Verliehene Medien ", 1);
    printArticleHeader();
    printSeparator("", 0);
    articles = getArticles();
    displayArticles(articles);
    printSeparator("", 0);
    printf("\ns - Medien sortieren\n");
    printf("\nf - Medien durchsuchen\n");
    printf("\nEingabe: ");
    fgets(buf, 128, stdin);
    action = buf[0];
    switch(action) {
        case 's': sortMenu(); break;
        case 'f': searchMenu(); break;
        default: break;
    }
}

int addArticlesMenu() {
    char proceed = 'j';
    Article* new;
    List* articles = getArticles();
    system("clear");
    printSeparator(" Medien hinzufügen ", 1);
    displayArticles(articles);
    printSeparator("", 0);
    do {
        new = createArticleInteractively();
        if (new == NULL) {
            printf("Erneut versuchen (j/n)?: ");
            fgets(buf, 128, stdin);
            if (buf[0] == 'j') continue;
            else break;
        }
        printSeparator("", 0);
        printf("Zusammenfassung:\n");
        printArticle(new);
        printf("Artikel wurde hinzugefügt:\n");
        append(articles, new);
        printf("Weiteren Artikel hinzufügen (j/n)? ");
        fgets(buf, sizeof(buf), stdin);
        proceed = buf[0];
    } while (proceed == 'j');
    saveArticles(articles);
    return 0;
}

int deleteArticlesMenu() {
    int id;
    char proceed = 'j';
    Article* old;
    List* articles = getArticles();
    system("clear");
    do {
        printSeparator(" Medien entfernen ", 1);
        displayArticles(articles);
        printSeparator("", 0);
        printf("ID des zu löschenden Mediums eingeben: ");
        fgets(buf, 128, stdin);
        buf[strlen(buf)-1] = '\0';
        if (!isValidId(buf)) {
            printf("FEHLER: ID darf nur Ziffern enthalten und hat maximal zwei Stellen\n");
            printf("Erneut versuchen (j/n)?: ");
            fgets(buf, 128, stdin);
            if (buf[0] == 'j') {
                continue;
            } else {
                break;
            }
        }
        id = atoi(buf);
        old = searchById(articles, id);
        if (old) {
            printArticle(old);
            printf("Medium wirklich löschen (j/n)?: ");
            fgets(buf, 128, stdin);
            if (buf[0] == 'j') {
                removeArticleFromList(articles, old);
            }
        } else {
            printf("Es existiert kein Medium zur gesuchten ID %d\n", id);
            continue;
        }
        printSeparator("", 0);
        displayArticles(articles);
        printf("\nWeiteres Medium entfernen (j/n)?: ");
        fgets(buf, 128, stdin);
        proceed = buf[0];
        system("clear");
    } while (proceed == 'j');
    saveArticles(articles);
    return 0;
}

/********************* MAIN **************************/

int main() {
    char menu;
    do {
        system("clear");
        printMenu();
        fgets(buf, 128, stdin);
        menu = buf[0];
        switch (menu) {
            case 'l': displayArticlesMenu(); break;
            case 'h': printHelpMenu(); break;
            case 'a': addArticlesMenu(); break;
            case 'd': deleteArticlesMenu(); break;
            case 's': sortMenu(); break;
            case 'f': searchMenu(); break;
            default: printf("\nAnwendung verlassen...\n\n"); return 0;
        }
    } while (1);
}





