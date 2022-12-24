#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "article.h"

int main() {
    char proceed;
    int res;
    
    // FILE* pf = fopen("./articles.csv", "rt");
    // fscanf(pf, "%d,%d,%[^\n]", &id, &media, test);
    // for ()
    // // printf("%d, %d, %s, %s, %s\n", id, media, title, author, lender);
    // fclose(pf);
    
    
    
    Article* a;
    FILE* pf = fopen("data/articles.csv", "rt");
    while((a = readArticle(pf))!=NULL) {
        printArticle(a);
    }
    fclose(pf);
    
    
    
    
    
    
    // FILE* pf = fopen("./articles.csv", "at");
    // do {
    //     Article* a = createArticleInteractively();
    //     printArticle(a);
    //     res = writeArticle(pf, a);
    //     if (res < 0) {
    //         printf("Schreiben fehlgeschlagen\n");
    //         continue;
    //     }
    //     printf("Weiteren Artikel eingeben (j/n)? ");
    //     fgets(buf, 128, stdin);
    //     proceed = buf[0];
    // } while(proceed == 'j');
 
    exit(0);
}