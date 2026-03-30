#include <stdio.h>
/*
    nao usei ia.
*/
int main() {
    int x = 0, y = 0;
    char passos[42];
    fgets(passos, 42, stdin);

    // cria a cidade e inicializa com 0
    int cidade[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cidade[i][j] = 0;
        }
    }

    // percorre os passos e atualiza a cidade
    for(int i = 0; passos[i] != '\n' && passos[i] != '\0'; i += 2){
        if(passos[i] == 'b' && y < 3){
            y++;
            cidade[y][x] += 1;
        }      
        else if(passos[i] == 'c' && y > 0){
            y--;
            cidade[y][x] += 1;
        }  
        else if(passos[i] == 'd' && x < 3){
            x++;
            cidade[y][x] += 1;
        }
        else if(passos[i] == 'e' && x > 0){
            x--;
            cidade[y][x] += 1;
        }
    }

    x=0; 
    y=0;
    // percorre a cidade para encontrar a coordenada com o maior valor
    for(int i = 0; i < 4; i++){
        for(int j =0; j < 4 ; j++){
            if(cidade[i][j] > cidade[y][x]){
                y = i;
                x = j;
            }
        }
    }

    printf("Coordenada X:%d, Y:%d", x, y);

    return 0;
}