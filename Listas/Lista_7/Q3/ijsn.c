#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[201];
    int habitantes;
    int periculosidade;
    char funcao[201];
} Cidadela;


void percorrerMensagem(char *msg, Cidadela *cida){
    cida->nome[0] = '\0';
    cida->habitantes = 0;
    cida->periculosidade = 0;
    cida->funcao[0] = '\0';

    

}

void pegarChave(char *msg , int index){

}


int main(){
    char mensagem[201];
    int tamanho = 1;
    Cidadela *cida = malloc(sizeof(Cidadela) * tamanho);

    while(fgets(mensagem, sizeof(mensagem), stdin) != NULL){
        mensagem[strcspn(mensagem, "\n")] = '\0';

        if(strchr(mensagem, '!') != NULL){
            int index = strcspn(mensagem, "!");
            pegarChave(mensagem, index);

        }else{
            cida = realloc(cida, sizeof(Cidadela) * tamanho);
            percorrerMensagem(mensagem, &cida[tamanho - 1]);
            tamanho++;
        }
    }


    return 0;
}