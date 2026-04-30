#include <stdio.h>
#include <stdlib.h>

int main(){
    int *ponteiro = NULL;
    int tamanho_original = 0, tamanho = 0;
    int valor;

    while(scanf("%d",&valor) != EOF){
        ponteiro = (int *) realloc(ponteiro, (tamanho + 1) * 4);
        ponteiro[tamanho] = valor;
        tamanho++;
    }
    tamanho_original = tamanho;
    printf("Sequencia original: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", ponteiro[i]);
    }
    printf("\n");
    printf("Comprimento original: %d\n",tamanho_original);


    int alterou = 1;
    while(alterou){
        alterou = 0;
        for(int i = 0; i < tamanho - 1; i++){
            if(ponteiro[i] == ponteiro[i+1]){
                if(ponteiro[i]==7){
                    ponteiro[i] = 1; 
                }else{
                    ponteiro[i] += 1;
                }

                // puxa os elementos uma casa para traz
                for(int j = i+1; j < tamanho - 1; j++){
                    ponteiro[j] = ponteiro[j+1];
                }
                tamanho--;
                alterou = 1;            
                break;                   
            }
        }
    }
    int soma = 0;
    printf("Sequencia harmonizada: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", ponteiro[i]);
        soma += ponteiro[i];
    }
    printf("\n");
    printf("Comprimento final: %d\n",tamanho);
    printf("Soma harmonizada: %d", soma);

    return 0;
}