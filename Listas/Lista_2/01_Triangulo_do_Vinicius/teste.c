#include <stdio.h>

/*
=== A partir dessa lista deixarei as explicações no proprio código ===
- Não foi utilizado ia para resolver o problema, apenas raciocínio lógico.
*/

int main(){
    char L;
    scanf("%c", &L);

    int x = L - 'A'; // x = quantas letras tem a linha mais larga - 1( que é a letra A), sera usado na impressão dos pontos )
    // x == 0 | representa que a letra A é a linha mais larga, ou seja, tem apenas 1 letra e nenhum ponto.

    for(int i = 'A'; i <= L; i++){ // vai de A até a letra em 'L'

        // imprime os pontos a esquesda, a quantidade de pontos é igual a quantidade de letras da linha mais larga - 1 (x)
        for(int j = 0; j < x ; j++) printf("."); 

        // imprime as letras ate a atual, que representada por 'i'
        for(int j = 'A'; j <= i; j++) printf("%c", j);
        
        // faz o mesmo processo, mas de forma decrescente, ou seja, imprime as letras de atual - 1 (i-1) até a letra A
        for(int j = i-1 ; j >= 'A' ; j--) printf("%c", j);
        
        // imprime os pontos a direita 
        for(int j = 0; j < x ; j++) printf(".");
        
        x--;// diminue a quantidade de pontos a serem impressos a cada linha
        
        printf("\n");
    }

    return 0;
}