#include <stdio.h>
#define S 102

int main() {
    char string[S];
    fgets(string, S, stdin);

    printf("%s\n", string);

    // conoverta tudo para minusculo
    for(int i = 0; string[i] != '\0'; i++) {
        unsigned char l = string[i];
        printf("%c\n ", l);

        if(l >= 'A' && l <= 'Z') string[i] = string[i] + 32;

        printf("%c\n", string[i]);
    }

    return 0;
}