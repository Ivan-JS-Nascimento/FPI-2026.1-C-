#include <stdio.h>
#include <stdlib.h>
#include <string.h> // sem essa linha as linhas 48, 49 e 50 não funcionam

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

typedef struct {
    int codigo;
    char tipo;
    int quantidade;
} Movimento;

typedef struct {
    int  codigo;
    char tipo;
    int  quantidade;
    char motivo[50];
} Inconsistencias;

//-----------------------------------------
void registrar_inconsistencia(
    Inconsistencias **inc, 
    int  *quantidade_inc, 
    int  *tamanho_inc, 
    int  codigo, 
    char tipo, 
    int  quantidade, 
    char *motivo)
{
        
    if(*quantidade_inc == *tamanho_inc){
        *tamanho_inc += 2;
        Inconsistencias *temp = realloc(*inc, *tamanho_inc * sizeof(Inconsistencias));
        if(temp == NULL){
            free(*inc);
            exit(1);
        }
        *inc = temp;
    }
    (*inc)[*quantidade_inc].codigo = codigo;
    (*inc)[*quantidade_inc].tipo = tipo;
    (*inc)[*quantidade_inc].quantidade = quantidade;
    strcpy((*inc)[*quantidade_inc].motivo, motivo);
    (*quantidade_inc)++;
}
//-----------------------------------------

int main(){
    int quantidade_p = 0, quantidade_m = 0, tamanho_p = 2, tamanho_m = 2;
    Produto   *produtos   = malloc(tamanho_p * sizeof(Produto));
    Movimento *movimentos = malloc(tamanho_m * sizeof(Movimento));
    if(produtos == NULL || movimentos == NULL) return 1;

    FILE *produto_file = fopen("produtos.txt", "r");
    if(produto_file == NULL){
        printf("Erro ao abrir o arquivo produtos.txt\n");
        free(produtos);
        free(movimentos);
        return 1;
    }
    // leitura dos produtos e armazenamento dos dados nas structs, com realocação dinâmica caso necessário
    while(fscanf(produto_file, "%d %s %d %f", 
        &produtos[quantidade_p].codigo, 
         produtos[quantidade_p].nome, 
        &produtos[quantidade_p].quantidade,
        &produtos[quantidade_p].preco) == 4){
        
        quantidade_p++;
        if(quantidade_p == tamanho_p){
            Produto *temp = realloc(produtos, (tamanho_p+=2) * sizeof(Produto));
            if(temp == NULL){
                fclose(produto_file);
                free(produtos);
                free(movimentos);
                return 1;
            }
            produtos = temp;
        }
    }
    fclose(produto_file);

    FILE *movimento_file = fopen("movimentos.txt", "r");
    if(movimento_file == NULL){
        printf("Erro ao abrir o arquivo movimentos.txt\n");
        free(produtos);
        free(movimentos);
        return 1;
    }
    // leitura dos movimentos e armazenamento dos dados nas structs, com realocação dinâmica caso necessário
    while(fscanf(movimento_file, "%d %c %d", 
        &movimentos[quantidade_m].codigo, 
         &movimentos[quantidade_m].tipo, 
        &movimentos[quantidade_m].quantidade) == 3){

        quantidade_m++;
        if(quantidade_m == tamanho_m){
            Movimento *temp = realloc(movimentos, (tamanho_m+=2) * sizeof(Movimento));
            if(temp == NULL){
                fclose(movimento_file);
                free(movimentos);
                free(produtos);
                return 1;
            }
            movimentos = temp;
        }
    }
    fclose(movimento_file);

// ========================================
//  Realizando os movimentos e registrando as inconsistências
    int produtos_processados = quantidade_p;
    int movimentos_aplicados = 0;
    int saidas_recusadas     = 0;
    int sem_cadastro         = 0;
    int tamanho_inc = 2, quantidade_inc = 0;
    Inconsistencias *inc = malloc(tamanho_inc * sizeof(Inconsistencias));
    for(int i=0; i<quantidade_m; i++){
        int produtos_achados = 0;
        for(int j=0; j<quantidade_p; j++){
            if(movimentos[i].codigo == produtos[j].codigo){
                produtos_achados++;
                if(movimentos[i].tipo == 'E'){
                    produtos[j].quantidade += movimentos[i].quantidade;
                    movimentos_aplicados++;
                } else if(movimentos[i].tipo == 'S'){
                    if(produtos[j].quantidade >= movimentos[i].quantidade){
                        produtos[j].quantidade -= movimentos[i].quantidade;
                        movimentos_aplicados++;
                    } else {
                        // inconsistencia: estoque insuficiente
                        registrar_inconsistencia(&inc, &quantidade_inc, &tamanho_inc, movimentos[i].codigo, movimentos[i].tipo, movimentos[i].quantidade, "ESTOQUE_INSUFICIENTE");
                        saidas_recusadas++;
                    }
                    
                }
            }
        }
        if(produtos_achados == 0){
            // inconsistencia: produto inexistente
            registrar_inconsistencia(&inc, &quantidade_inc, &tamanho_inc, movimentos[i].codigo, movimentos[i].tipo, movimentos[i].quantidade, "PRODUTO_INEXISTENTE");
            sem_cadastro++;
        }
    }
// ---------------------------------------
//  passandos os produtos para o estoque
    FILE *estoque_file = fopen("estoque_atualizado.txt", "w");
    if(estoque_file == NULL){
        printf("Erro ao criar o arquivo estoque_produtos.txt\n");
        free(produtos);
        free(movimentos);
        free(inc);
        return 1;
    }
    for(int i=0; i<quantidade_p; i++){
        fprintf(estoque_file, "%d %s %d %.2f\n", 
            produtos[i].codigo, 
            produtos[i].nome, 
            produtos[i].quantidade, 
            produtos[i].preco);
    }
    fclose(estoque_file);
//  cirando relatorio
    FILE *relatorio_file = fopen("relatorio.txt", "w");
    if(relatorio_file == NULL){
        printf("Erro ao criar o arquivo relatorio.txt\n");
        free(produtos);
        free(movimentos);
        free(inc);
        return 1;
    }
    fprintf(relatorio_file, "======== RELATÓRIO DE MOVIMENTAÇÕES ========\n");
    fprintf(relatorio_file, "PRODUTOS PROCESSADOS: %d\n", produtos_processados);
    fprintf(relatorio_file, "MOVIMENTOS APLICADOS: %d\n", movimentos_aplicados);
    fprintf(relatorio_file, "SAÍDAS RECUSADAS: %d\n", saidas_recusadas);
    fprintf(relatorio_file, "MOVIMENTOS SEM CADASTRO: %d\n", sem_cadastro);
    fprintf(relatorio_file, "ESTOQUE BAIXO:\n");
    for(int i=0; i<quantidade_p; i++){
        if(produtos[i].quantidade <= 5){
            fprintf(relatorio_file, "%d %s %d\n", 
                produtos[i].codigo, 
                produtos[i].nome, 
                produtos[i].quantidade);
        }
    }
    fprintf(relatorio_file, "INCONSISTENCIAS:\n");
    for(int i=0; i<quantidade_inc; i++){
        fprintf(relatorio_file, "%d %c %d %s\n", 
            inc[i].codigo, 
            inc[i].tipo, 
            inc[i].quantidade, 
            inc[i].motivo);
    }
    fclose(relatorio_file);

    free(produtos);
    free(movimentos);
    free(inc);
    return 0;
}