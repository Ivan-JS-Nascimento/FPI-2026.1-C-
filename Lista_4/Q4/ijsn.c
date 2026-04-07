#include <stdio.h>

/*
 esse codigo eu criei do zero
*/
#define S 102

int main() {
    int linha, coluna;
    scanf("%dx%d", &linha, &coluna);

    char map_area2[S][S];
    int distancia[S][S]; // para calculara a distancia
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

            distancia[i][j] = -1; // Inicializa a matriz de distancias com -1
        }
    }

    // indice 0 = esquerda, 1 = direita, 2 = baixo, 3 = cima
    int x[] = {-1, 1,  0, 0};
    int y[] = { 0, 0, -1, 1};
    distancia[oy][ox] = 0; 
    // a logica é criar varios clones para todos os caminhos possiveis , o que chegar primeiro eu conto as casas que ele andou.
    int clone_das_sombras = 0;

    while (distancia[dy][dx] == -1) {
        for (int i = 0; i < linha; i++) {     // percorrer mapa
            for (int j = 0; j<coluna; j++) {  // percorrer mapa

                if (distancia[i][j] == clone_das_sombras && map_area2[i][j] != '#') { // se for um local valido para andar

                    for (int k=0; k<4; k++) { // percorre as ortogonais
                        if ((i + y[k] >= 0 && i + y[k] < linha) && (j + x[k] >= 0 && j + x[k] < coluna) && (map_area2[i + y[k]][j + x[k]] != '#')) { // se estiver dentro do mapa
                            if (distancia[i + y[k]][j + x[k]] == -1) { // se ainda nao foi visitado
                                distancia[i + y[k]][j + x[k]] = distancia[i][j] + 1;
                            }
                        }  
                    }
                }
            }
        }
        // descomente essa parte caso queira ver a matriz de distancias a cada passo
        // for (int w = 0; w < linha; w++) {
        //     for (int z = 0; z < coluna; z++) {
        //         printf("%d ", distancia[w][z]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
        clone_das_sombras++;
        if(clone_das_sombras > linha * coluna){ // se ainda tiver caminhos para andar o while continua
                break;
        }
    }
    if(distancia[dy][dx] == -1){ // se o destino ainda tiver -1, significa que nao foi possivel chegar
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }else{
        printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", clone_das_sombras);
    }
    return 0;
}