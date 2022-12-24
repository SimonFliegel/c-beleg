#include <stdlib.h>
#include <stdio.h>
#include "administration.h"

int main() {
    List* articles = getArticles();
    displayArticles(articles);
    // only prints lender?
    exit(0);
}