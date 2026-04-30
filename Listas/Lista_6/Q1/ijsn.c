#include <stdio.h>
#include <stdlib.h>

// ----------- alocar memoria
int** alocar(int L, int C){
    int **mat = (int**) malloc(L * sizeof(int*));
    for(int i = 0; i < L ;i++){
        mat[i] = (int**) malloc(C * sizeof(int));
    }
    return mat;
}
// ------------ Ler matriz
void ler(int **mat, int L, int C){
    for(int i = 0; i < L ;i++){
        for(int j = 0; j < C ;j++){
            scanf("%d", &mat[i][j]);
        }
    }
}

// ----------- imprimir
void imprimir(int **mat, int L, int C){
    for(int i = 0; i < L ;i++){
        for(int j = 0; j < C ;j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
// ------------ liberar
void liberar(int **mat, int L){
    for(int i = 0; i < L ;i++){
        free(mat[i]);
    }
    free(mat);
}

int dobro(int x){ return x * 2;}
int quadrado(int x){ return x * x;}
int absoluto(int x){ return x < 0 ? -x : x;}

// ----------- aplicar a operacao na matriz
void aplica(int **mat, int L, int C, int(*op)(int)){
    for(int i = 0; i < L ;i++){
        for(int j = 0; j < C ;j++){
            mat[i][j] = op(mat[i][j]);
        }
    }
}



int main(){
    int L, C, escolha;
    scanf("%d %d", &L, &C);

    int **matriz = alocar(L, C); // criamos a matriz, mas ainda esta vazia

    ler(matriz, L, C);

    scanf("%d", &escolha);

    int (*operacao)(int);
    if(escolha == 1) operacao = dobro;
    if(escolha == 2) operacao = quadrado;
    if(escolha == 3) operacao = absoluto;

    aplica(matriz, L, C, operacao);
    imprimir(matriz, L, C);
    liberar(matriz, L);


    return 0;
}
