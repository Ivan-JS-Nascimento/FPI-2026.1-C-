#include <stdio.h>
#define SIZE 100

/*
 Nao ouve uso de ia para resolver o problema diretamente, apenas para duvidas e casos de teste.
*/

int main() {
    int T, N;
    scanf("%d", &T);

    for (int i = 0; i < T; i++){ // para cada T(casos de teste) 
        scanf("%d", &N); // recebemos um N com o número de elementos do vetor
        int X[SIZE];

        for (int j = 0; j < N; j++) scanf("%d", &X[j]); // recebe os elementos do vetor

        int melhor_index_inicio = 0, melhor_tamanho = 1, index_inicio_atual = 0, tamanho_atual = 1;

        for (int j = 0; j < N-1; j++){ // percorremos o vetor comparando com o elemento a direita dele
            if( X[j] > X[j+1] ){ // se o elemento for maior que o próximo, temos uma sequência decrescente, então aumentamos o tamanho atual
                tamanho_atual++;

            } else { // se o elemento for menor ou igual ao próximo, a sequência decrescente termina, 
                
                if( tamanho_atual > melhor_tamanho){         // se o tamanho atual for maior que o melhor tamanho encontrado:
                    melhor_index_inicio = index_inicio_atual; // atualizamos o melhor indice de inicio 
                    melhor_tamanho = tamanho_atual;           // e o melhor tamanho 
                }
                index_inicio_atual = j+1;
                tamanho_atual = 1;

            }
        }
        // verificamos novamente no final caso alguma sequencia decrescente termine no final do vetor
        if( tamanho_atual > melhor_tamanho ){         
            melhor_index_inicio = index_inicio_atual;
            melhor_tamanho = tamanho_atual;
        }
        
        if(melhor_tamanho > 1){ // se o melhor tamanho for maior que 1, imprimimos a sequência decrescente
            printf("%d\n", melhor_tamanho);
            for (int j = melhor_index_inicio; j < (melhor_index_inicio + melhor_tamanho) ; j++){
                printf("%d ", X[j]);
            }
            printf("\n");
        }else{
            printf("0\n");
        }
        
    }
    

    return 0;
}