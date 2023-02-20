#include <stdlib.h>
#include <stdio.h>
#include "../article.h"

int main() {
    int ret;
    ret = getAvailableId();
    printf("return-value: %d\n", ret);

    return 0;
}