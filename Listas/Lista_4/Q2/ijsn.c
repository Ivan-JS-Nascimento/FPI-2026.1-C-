#include <stdio.h>
/*
    nao usei ia.
*/
int main() {
    int m, n; // altura e largura da matriz(parede)
    scanf("%d %d", &m, &n);

    char parede[m][n+1];
    for (int i = 0; i < m; i++) {
        scanf("%s", parede[i]);
    }

    // percorre a parede
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {

            if (parede[i][j] == 'o') { // se encontrar uma gota
                if(i+1 < m){
                    if(parede[i+1][j]=='#'){ // achou uma prateleira
                        
                        // procurar bordas da prateleira
                        for(int k = j-1; k >= 0; k--){// para a esquerda
                            if(parede[i+1][k] == '#'){
                                parede[i][k] = 'o';
                            }else{
                                parede[i][k]   = 'o';
                                parede[i+1][k] = 'o';
                                break;
                            }
                        }
                        for(int k = j+1 ; k <n ; k++){// para a direita
                            if(parede[i+1][k] == '#'){
                                parede[i][k] = 'o';
                            }else{
                                parede[i][k]   = 'o';
                                parede[i+1][k] = 'o';
                                break;
                            }
                        }

                    }else{ // nao tem nada embaixo
                        parede[i+1][j] = 'o';
                    }
                }
            }
        }
    }

    // printa a parede no final
    for (int i = 0; i < m; i++) {
        printf("%s\n", parede[i]);
    }

    return 0;
}