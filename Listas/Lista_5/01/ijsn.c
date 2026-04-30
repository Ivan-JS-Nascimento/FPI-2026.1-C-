#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ouve auxilio de ia para aprender os conceitos de ponteiros e alocação dinâmica.

int main() {
    int n;
    scanf("%d\n", &n);

    char **ponteirao = malloc(n * sizeof(char *)); // cria um ponteirão com 2 dimensoes

    if (!ponteirao) {
        fprintf(stderr, "Erro ao alocar array de strings\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        char buffer[1024];
        fgets(buffer, sizeof(buffer), stdin);

        // Remove o '\n' do final se existir
        buffer[strcspn(buffer, "\n")] = '\0';

        // Aloca exatamente o tamanho necessário
        char *temp = malloc((strlen(buffer) + 1) * sizeof(char));
        if (!temp) {
            fprintf(stderr, "Erro ao alocar string %d\n", i);
            return 1;
        }

        strcpy(temp, buffer);
        ponteirao[i] = temp;
    }

    // Calcula o tamanho total da merged
    int total = 0;
    for (int i = 0; i < n; i++)
        total += strlen(ponteirao[i]);

    // Aloca a merged string
    char *merged = malloc((total + 1) * sizeof(char));
    if (!merged) {
        fprintf(stderr, "Erro ao alocar merged\n");
        return 1;
    }

    // Percorre coluna por coluna (índice i de cada string)
    int pos = 0;          // posição atual na merged
    int ainda_tem = 1;    // controle de parada

    for (int i = 0; ainda_tem; i++) {
        ainda_tem = 0;    // assume que acabou, até provar o contrário

        for (int j = 0; j < n; j++) {
            if (i < strlen(ponteirao[j])) {       // string j ainda tem caractere na coluna i?
                merged[pos++] = ponteirao[j][i];
                ainda_tem = 1;                  // ainda tem pelo menos uma string com caractere
            }
        }
    }

    merged[pos] = '\0';
    printf("%s\n", merged);

    int i = 0, op = 1;
    while (i < strlen(merged) - 1 ) {
        if (merged[i] == merged[i + 1]) {

            // Fusão: próximo caractere ASCII, 'z' vira 'a'
            char novo;
            if(merged[i] == 'z'){
                novo = 'a';
            }else{
                novo = merged[i] + 1;
            }

            // Substitui o atual pelo novo caractere
            merged[i] = novo;

            // Remove o próximo (shift para a esquerda)
            for (int j = i + 1; j < strlen(merged); j++)
                merged[j] = merged[j + 1];

            // Retrocede (mas não passa do índice 0)
            if(i>0){
                i--;
            }
        }else{
            i++;
        }
    }

    printf("%s\n", merged);

    return 0;
}