#include <stdio.h>

/*
 esse é o codigo que eu criei e nao consegui testalo devido a queda do the huxley, tem como base a logica de teste.c
*/
#define S 102

int main() {
    int linha, coluna;
    scanf("%dx%d", &linha, &coluna);

    char map_area2[linha][coluna+1];
    for(int i=0; i<linha; i++){
        scanf("%s", map_area2[i]);
    }

    // Encontra coordenadas de origem e destino e preenche a copia do mapa
    int oy = -1, ox = -1, dy = -1, dx = -1;
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if (map_area2[i][j] == 'o') {
                oy = i; ox = j; 
            }
            if (map_area2[i][j] == 'd') {
                dy = i; dx = j; 
            }
        }
    }

    // indice 0 = esquerda, 1 = direita, 2 = baixo, 3 = cima
    int x[] = {-1, 1,  0, 0};
    int y[] = { 0, 0, -1, 1};
    map_area2[oy][ox] = '0';
    // a logica é criar varios clones para todos os caminhos possiveis , o que chegar primeiro eu conto as casas que ele andou.
    int clone_das_sombras = 0, verificador_de_possibilidade = 0, mais_uma_vez = 0;

    while (map_area2[dy][dx]=='d') {
        for (int i = 0; i < linha; i++) {     // percorrer mapa
            for (int j = 0; j<coluna; j++) {  // percorrer mapa
                if (map_area2[i][j] == '0') {
                    for (int k=0; k<4; k++) { // percorre as ortogonais
                        if (i + y[k] >= 0 && i + y[k] < linha && j + x[k] >= 0 && j + x[k] < coluna) { // se estiver dentro do mapa
                            if (map_area2[i + y[k]][j + x[k]] != '#' && map_area2[i + y[k]][j + x[k]] != '0') { // se nao for uma parede ou um local com numero
                                map_area2[i + y[k]][j + x[k]] = '0';
                                clone_das_sombras++;
                                verificador_de_possibilidade = 0;

                                // for (int w = 0; w < linha; w++) {
                                //     printf("%s\n", map_area2[w]);
                                // }
                                // printf("\n");
                            }
                        }  
                    }
                }
            }
        }
        for(int i = 0; i < linha; i++){
            for(int j = 0; j < coluna; j++){
                if(map_area2[i][j] == '_'){
                    verificador_de_possibilidade++;
                }
            }
        }
        if(verificador_de_possibilidade == 0){
            if(mais_uma_vez == 1){
                map_area2[dy][dx] = 'X';
            }
            mais_uma_vez++;
        }
    }
    //printf("%d\n", clone_das_sombras);

    if(map_area2[dy][dx] == 'X'){
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }else{
        printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", clone_das_sombras);
    }

    
    return 0;
}