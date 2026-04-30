#include <stdio.h>
#include <stdlib.h>

// nao usei ia, a logica ta bem simples de entender.

int main(){
    printf("Mais um bom dia de trabalho!\n");

    int *ponteiro = NULL; // ponteiro inicializado como NULL

    int valor, tamanho = 0;
    while(scanf("%d", &valor) != EOF){ // lê até o final da entrada
        ponteiro = (int *) realloc(ponteiro, (tamanho + 1) * sizeof(int)); // realoca memoria para um novo inteiro
        ponteiro[tamanho] = valor; // guarda o valor lido no ponteiro
        tamanho++;
    }

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < tamanho; j++){
            if(i == 1){
                if(ponteiro[j] % 2 == 0 ) printf("%d\n", ponteiro[j]); // printa os números pares
            }else{
                if(ponteiro[j] % 2 != 0 ) printf("%d\n", ponteiro[j]); // printa os números ímpares
            }
        }
    }

    free(ponteiro); // libera a memmoria

    printf("Vou visitar esses lugares de novo... algum dia.\n");
    return 0;
}