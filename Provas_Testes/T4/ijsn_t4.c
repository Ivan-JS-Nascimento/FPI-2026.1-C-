// Teste 4 - Espiral Numérica - 06/04/2026

#include <stdio.h>

int comparar(int n1, int n2){
//   verifica se n1 e n2 estao de acordo com isso:
//    Dois números consecutivos na espiral formam um par válido quando satisfazem simultaneamente:
//      Mesma soma de dígitos (ex.: 91 e 46 ambos somam 10).
//      O primeiro é estritamente maior que o segundo.

    int soma_n1, soma_n2;
    if(n1>n2){
        //------------------------------------------
        if(n1>99){ // 3 digitos
            int a1 = n1/100; 
            int a2 = (n1 - a1*100)/10;
            int a3 = n1 - a1*100 - a2*10;

            soma_n1 = a1+a2+a3;

        }else if(n1>9){ // 2 digitos
            int a2 = n1/10;
            int a3 = n1 - a2*10;

            soma_n1 = a2+a3;

        }else{
            soma_n1 = n1;
        }
        //------------------------------------------
        if(n2>99){ // 3 digitos
            int a1 = n2/100; 
            int a2 = (n2 - a1*100)/10;
            int a3 = n2 - a1*100 - a2*10;

            soma_n2 = a1+a2+a3;

        }else if(n2>9){ // 2 digitos
            int a2 = n2/10;
            int a3 = n2 - a2*10;

            soma_n2 = a2+a3;

        }else{
            soma_n2 = n2;
        }
        //-----------------------------------------

        if(soma_n1 == soma_n2){
            return 1;
        }


    }
    return 0;
}

int main(){

    int N, valor;
    scanf("%d", &N);
    int matriz[N][N], clone_matriz[N][N];

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            scanf("%d", &valor);
            matriz[i][j] = valor;
            clone_matriz[i][j] = 0; // nao visitado = 0 | visitado  = 1
        }
    }

    int tamanho_linha_maior = 0;
    int coordenadas_maior[N*N][2];

    int coordenadas[N*N][2];
    char sentido = 'd';

    for(int i=0; i<N*N; i++){
        for(int j = 0; j<2; j++){
            coordenadas[i][j] = -1;
            coordenadas_maior[i][j] = -1;
        }
    }

    // percorrendo matriz em espiral
    int i=0, j=0, cont = 0;
    for(int k=0; k<N*N; k++){
        int n1=0, n2=0;
        int x1, y1;
        n1 = matriz[i][j];
        x1 = j, y1 = i;
        clone_matriz[i][j] = 1;

        //---------- moviento do vetor para pegar o segundo numero -------------
        if(sentido == 'd'){
            if(j<N-1 && clone_matriz[i][j+1]==0){
                j++;
                n2 = matriz[i][j];
                clone_matriz[i][j] = 1;
            }else{ // chegou na borda
                sentido = 'b';
            }
        }
        if(sentido=='b'){
            if(i<N-1 && clone_matriz[i+1][j]==0){
                i++;
                n2 = matriz[i][j];
                clone_matriz[i][j] = 1;
            }else{ // chegou na borda
                sentido = 'e';
            }
        }
        if(sentido=='e'){
            if(j>0 && clone_matriz[i][j-1]==0){
                j--;
                n2 = matriz[i][j];
                clone_matriz[i][j] = 1;
            }else{ // chegou na borda
                sentido = 'c';
            }
        }
        if(sentido=='c'){
            if(i>0 && clone_matriz[i-1][j]==0){
                i--;
                n2 = matriz[i][j];
                clone_matriz[i][j] = 1;
            }else{ // chegou na borda
                sentido = 'd';
            }
        }
        // ------------------------------------------------------------------

        if(comparar(n1, n2)){
            cont++;
            for(int l=0; l<N*N; l++){
                for(int p = 0; p<2; p++){
                    if(coordenadas[0][0]== -1){ // coord de n1, colocada apenas uma vez
                        coordenadas[0][0] = y1;
                        coordenadas[0][1] = x1;
                        break;
                    }
                    if(coordenadas[l][p] == -1){ // coord de n2
                        coordenadas[l][0] = i;
                        coordenadas[l][1] = j;
                        l=N*N;
                        break;
                    }
                }
            }
            
            if(cont>tamanho_linha_maior){ // se for maior do que a maior anterior
                tamanho_linha_maior = cont;
                for(int l=0; l<N*N; l++){
                    for(int p = 0; p<2; p++){
                        coordenadas_maior[l][p] = coordenadas[l][p];
                    }
                }
            }

        }else{
            // reseta o contador e as cordenadas anteriores
            cont=0;
            for(int l=0; l<N*N; l++){
                for(int p = 0; p<2; p++){
                    coordenadas[l][p] = -1;
                }
            }
        }
    }

    // prints finais
    if(tamanho_linha_maior+1 >= 2){
        printf("%d\n", tamanho_linha_maior+1);
        for(int i = 0 ; i < N*N; i++){
            if(coordenadas_maior[i][0] != -1){
                printf("(%d,%d)\n", coordenadas_maior[i][0], coordenadas_maior[i][1]);
            }else{
                break;
            }
        }
    }else{
        printf("0\n");
    }
    



    return 0;
}