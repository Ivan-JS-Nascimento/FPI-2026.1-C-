#include <stdio.h>
/*
 usei ia, ela deu a ideia de usar dois vetores para os movimentos ortogonais e diagonais
 o que é mais pratico e limpo do que usar 8 if's diferentes para cada direção.
*/
int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    char grid[100][101];
    for (int i = 0; i < m; i++) {
        scanf("%s", grid[i]);
    }

    // vetores para movimentos ortogonais e diagonais
    int ortagonal_i[] = {-1, 1,  0, 0};
    int ortagonal_j[] = { 0, 0, -1, 1};
    int diagonal_i[]  = {-1, -1, 1,  1};
    int diagonal_j[]  = {-1,  1, -1, 1};

    // percorre a grade para encontrar os 'P'
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {

            if (grid[i][j] == 'P') {
                // Ortogonais -> '+'
                for (int d = 0; d < 4; d++) { // pra cada valor de d, pegamos uma direção ortogonal diferente
                    int novo_i = i + ortagonal_i[d];
                    int novo_j = j + ortagonal_j[d];
                    // se nao sair da grade e for '-' ou 'x', marca como '+'
                    if (novo_i >= 0 && novo_i < m && novo_j >= 0 && novo_j < n && (grid[novo_i][novo_j] == '-' || grid[novo_i][novo_j] == 'x')){
                        grid[novo_i][novo_j] = '+';
                    }
                        
                }
                // Diagonais -> 'x' (só se ainda for '-')
                for (int d = 0; d < 4; d++) { // para cada valor de d, pegamos uma direção diagonal diferente
                    int novo_i = i + diagonal_i[d];
                    int novo_j = j + diagonal_j[d];
                    // se nao sair da grade e for '-', marca como 'x'
                    if (novo_i >= 0 && novo_i < m && novo_j >= 0 && novo_j < n && grid[novo_i][novo_j] == '-'){
                        grid[novo_i][novo_j] = 'x';
                    }
                }
            }
        }
    }

    // printa a grade no final
    for (int i = 0; i < m; i++) {
        printf("%s\n", grid[i]);
    }

    return 0;
}