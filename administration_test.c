#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "administration.h"

int main() {
    char buffer[128];
    char* string_id;
    char* searchString = "Stein der Weisen";
    Media media = Cd;
    
    List* articles = getArticles();
    List* results;

    displayArticles(articles);

    Article* result = searchById(articles, 7);

    printArticle(result);


    // results = searchByTitle(articles, searchString);
    // printf("============== Ausgabe ================\n");
    // displayArticles(results);

    

    






    // printf("Artikel nach ID durchsuchen: ");
    // fgets(buffer, sizeof(buffer), stdin);
    // buffer[strlen(buffer)-1] = '\0';
    // string_id = malloc(strlen(buffer)+1);
    // strcpy(string_id, buffer);
    // if (isValidId(string_id)) {
    //     id = atoi(string_id);
    // }
    // printf("id: %d\n", id);
    // result = searchById(articles, id);
    // if (result) {
    //     printArticle(result);
    // }
    exit(0);
}