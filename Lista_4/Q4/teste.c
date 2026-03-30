#include <stdio.h>
// codigo gerado po ia.
// aprendendo esse tal de BFS
int main() {
    // 1. Representando o Grafo (Matriz 5x5)
    // Se G[i][j] é 1, existe uma linha ligando os dois números
    int grafo[5][5] = {
        {0, 1, 1, 0, 0}, // O nó 0 liga com 1 e 2
        {1, 0, 0, 1, 1}, // O nó 1 liga com 0, 3 e 4
        {1, 0, 0, 0, 1}, // O nó 2 liga com 0 e 4
        {0, 1, 0, 0, 0}, // O nó 3 liga com 1
        {0, 1, 1, 0, 0}  // O nó 4 liga com 1 e 2
    };

    int visitado[5] = {0, 0, 0, 0, 0}; // 0 = não visitado, 1 = visitado
    int fila[5]; 
    int inicio = 0, fim = 0;

    // Começando pelo nó 0
    int noInicial = 0;
    visitado[noInicial] = 1;
    fila[fim] = noInicial; // Coloca o 0 na fila
    fim++;

    printf("Ordem da BFS: ");

    // Enquanto a fila não estiver vazia
    while (inicio < fim) {
        int atual = fila[inicio]; // Pega quem está na frente da fila
        inicio++;
        printf("%d ", atual);

        // Olha na matriz quem são os vizinhos do nó "atual"
        for (int vizinho = 0; vizinho < 5; vizinho++) {
            // Se tem conexão (1) e eu ainda não visitei (0)
            if (grafo[atual][vizinho] == 1 && visitado[vizinho] == 0) {
                visitado[vizinho] = 1;   // Marca como visitado
                fila[fim] = vizinho;     // Coloca no fim da fila para visitar depois
                fim++;
            }
        }
    }

    return 0;
}
