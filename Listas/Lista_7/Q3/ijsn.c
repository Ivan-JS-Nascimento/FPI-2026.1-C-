#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[201];
    int habitantes;
    int periculosidade;
    char funcao[201];
} Cidadela;

int lexigrafica(char *nome1, char *nome2){
    int i;
    for(i=0 ; nome1[i]!='\0' && nome2[i]!='\0' ; i++){
        if(nome1[i] - nome2[i] != 0) return nome1[i] - nome2[i];
    }

    if(nome1[i] == '\0' && nome2[i] != '\0') return -1;
    if(nome1[i] != '\0' && nome2[i] == '\0') return  1;

    return 0;
}

void organizarCidadelas(Cidadela *cida, int t){
// decrescente 
    for(int i=0 ; i<t-1 ; i++){
        for(int j=0 ; j<t-1-i ; j++){
            // ordene pelo número de habitantes
            if(cida[j].habitantes < cida[j+1].habitantes){
                Cidadela copia = cida[j];
                cida[j] = cida[j+1];
                cida[j+1] = copia;
            
            // em caso de empate olhe o grau de periculosidade
            }else if(cida[j].habitantes == cida[j+1].habitantes && cida[j].periculosidade < cida[j+1].periculosidade){
                Cidadela copia = cida[j];
                cida[j] = cida[j+1];
                cida[j+1] = copia;
            // ordene por ordem lexigráfica se der empate de novo
            }else if(cida[j].habitantes == cida[j+1].habitantes && cida[j].periculosidade == cida[j+1].periculosidade && lexigrafica(cida[j].nome, cida[j+1].nome) > 0){
                Cidadela copia = cida[j];
                cida[j] = cida[j+1];
                cida[j+1] = copia;

            }
        }
    }
}

void formatarMensagem(char *msg){
    for(int i=0 ; msg[i]!='\0' ; i++){
        char m = msg[i];

        if( i==0 && m >= 'a' && m <= 'z' ) msg[0] = m - ('a' - 'A');
        if( i!=0 && m >= 'A' && m <= 'Z' ) msg[i] = m + ('a' - 'A');
    }
}

void percorrerMensagem(char *msg, Cidadela *cida){
    cida->nome[0] = '\0';
    cida->habitantes = 0;
    cida->periculosidade = 0;
    cida->funcao[0] = '\0';

    for(int i=0 ; msg[i]!='\0' ; i++){
        char m = msg[i];

        if(m >= 'A' && m <= 'Z'){
            int len = strlen(cida->nome);
            cida->nome[len] = m;
            cida->nome[len+1] = '\0';

        }else if(m >= '0' && m <= '9'){
            cida->habitantes = cida->habitantes * 10 + (m - '0');

        }else if(m == '*'){
            cida->periculosidade++;

        }else if(m == ' ' && msg[i+1] == ' '){
            int len = strlen(cida->funcao);
            cida->funcao[len] = msg[i+2];
            cida->funcao[len+1] = '\0';
        }
    }
    formatarMensagem(cida->nome);
    if(strlen(cida->funcao) > 0) formatarMensagem(cida->funcao);
}

void pegarChave(char *msg, int *chave){
    *chave = 0;
    for(int i=0 ; msg[i]!= '\0' ; i++){
        char m = msg[i];

        if(m >= '0' && m <= '9'){
            *chave = *chave * 10 + (m - '0');
        }
    }
}

void limpar(Cidadela *cida, int t){
    // for(int i=0 ; i<t-1 ; i++){
    //     printf("Cidadela: %s\nHabitantes: %d\nPericulosidade: %d\nFuncao: %s\n\n", cida[i].nome, cida[i].habitantes, cida[i].periculosidade, cida[i].funcao);
    // }
    cida = NULL;
    free(cida);
}

int main(){
    char mensagem[201];
    int tamanho = 1, chave = 0;
    Cidadela *cida = malloc(sizeof(Cidadela) * tamanho);

    while(fgets(mensagem, sizeof(mensagem), stdin) != NULL){
        mensagem[strcspn(mensagem, "\n")] = '\0';

        if(strchr(mensagem, '!') != NULL){
            int index = strcspn(mensagem, "!");
            pegarChave(mensagem, &chave);

        }else{
            if(tamanho != 1) cida = realloc(cida, sizeof(Cidadela) * tamanho);
            percorrerMensagem(mensagem, &cida[tamanho - 1]);
            tamanho++;
        }
    }

    organizarCidadelas(cida, tamanho);

    if(chave == 0){
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco. ");
    }else{
        printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade ", cida[chave - 1].nome, cida[chave - 1].habitantes, cida[chave - 1].funcao);
        for(int i=0 ; i<cida[chave-1].periculosidade ; i++){
            printf("*");
        }
        printf(". ");
        if(cida[chave-1].habitantes >= 1000 && cida[chave-1].periculosidade > 3){
            printf("Talvez seja melhor desistir...\n");
        }else{
            if(cida[chave-1].habitantes >= 1000) printf("Um lugar denso, vai ser difícil achar ela.\n");
            if(cida[chave-1].periculosidade > 3) printf("Vai ser complicado entrar lá.\n");
        }
    }

    limpar(cida, tamanho); 
    return 0;
}