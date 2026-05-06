#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char titulo[100];
    char genero[100];
    char studio[100];
    char console[100];
    int nota;
    int ano;
} Jogo;

void printAno(Jogo *colecao, int N, char *parametro){
    int x=0;
    for(int i=0 ; i<N ; i++){
        if(colecao[i].ano == atoi(parametro)){
            printf("%s\n", colecao[i].titulo);
            x++;
        }
    }
    if(x == 0) puts("Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
    else printf("Tenho %d jogos || %s.\n", x, parametro);
}

void printLetra(Jogo *colecao, int N, char *parametro){
    int x=0;
    for(int i=0 ; i<N ; i++){
        if(colecao[i].titulo[0] == parametro[0]){
            printf("%s\n", colecao[i].titulo);
            x++;
        }
    }
    if(x == 0) puts("Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
    else printf("Tenho %d jogos || %s.\n", x, parametro);
}

void printStudio(Jogo *colecao, int N, char *parametro){
    int x=0;
    for(int i=0 ; i<N ; i++){
        if(strcmp(colecao[i].studio, parametro) == 0){
            printf("%s\n", colecao[i].titulo);
            x++;
        }
    }
    if(x == 0) puts("Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
    else printf("Tenho %d jogos || %s.\n", x, parametro);
}

void printConsole(Jogo *colecao, int N, char *parametro){
    int x=0;
    for(int i=0 ; i<N ; i++){
        if(strcmp(colecao[i].console, parametro) == 0){
            printf("%s\n", colecao[i].titulo);
            x++;
        }
    }
    if(x == 0) puts("Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
    else printf("Tenho %d jogos || %s.\n", x, parametro);
}

void printColecao(Jogo *colecao, int N){
    for(int i=0 ; i<N ; i++){
        printf("%s %d\n", colecao[i].titulo, colecao[i].nota);
    }

}

int main(){
    int N;
    scanf("%d", &N);
    Jogo *colecao = malloc(N * sizeof(Jogo));
    for(int i=0 ; i<N ; i++){
        scanf("%s %s %s %s %d %d", 
            colecao[i].titulo, 
            colecao[i].genero, 
            colecao[i].studio, 
            colecao[i].console, 
            &colecao[i].nota, 
            &colecao[i].ano);
        if(colecao[i].nota > 7) puts("AWESOME! Mais um GOTY pra minha coleção!");
        if(colecao[i].nota < 4) puts("Era melhor jogar mais um jogo de Mahjong.");
    }
    char funcao[20];
    char parametro[50];

    while(scanf("%s", funcao) != EOF){
        if( strcmp(funcao, "printColecao") == 0) printColecao(colecao, N);
        else{
            scanf("%s", parametro);
            if(strcmp(funcao, "printAno") == 0) printAno(colecao, N, parametro);
            if(strcmp(funcao, "printLetra") == 0) printLetra(colecao, N, parametro);
            if(strcmp(funcao, "printStudio") == 0) printStudio(colecao, N, parametro);
            if(strcmp(funcao, "printConsole") == 0) printConsole(colecao, N, parametro);
        }
    }

    puts("Enjoei de jogar, agora vou ver TV.");
    free(colecao);
    
    return 0;
}