#include <stdio.h>
#include <string.h>

/*
    teve uso de ia diretamente.
*/

int main() {
    int R;
    scanf("%d", &R);

    char gigante[100000];
    int tamanho_gigante = 0;
    gigante[0] = '\0';

    for (int t = 0; t < R; t++) {
        char S[65];
        int C;
        scanf("%s %d", S, &C);

        int N = strlen(S);

        // Simula C clocks
        // Logica: led 0 sempre troca. Apos trocar, se ficou X (desligado),
        // o proximo led tambem troca. Propagacao para quando um led fica O (ligado).
        for (int c = 0; c < C; c++) {
            int deve_trocar = 1; // led 0 sempre troca
            for (int i = 0; i < N; i++) {
                if (deve_trocar) {
                    S[i] = (S[i] == 'O') ? 'X' : 'O';
                    deve_trocar = (S[i] == 'X'); // se ficou X, proximo troca
                } else {
                    deve_trocar = 0;
                }
            }
        }

        // Imprime resultado do caso teste
        printf("%s\n", S);

        // Monta a luz gigante
        if (tamanho_gigante == 0) {
            // Primeiro fio, apenas copia
            strcpy(gigante, S);
            tamanho_gigante = N;
        } else {
            // Determina ornamento
            char ultimo_gigante = gigante[tamanho_gigante - 1];
            char primeiro_fio   = S[0];
            int par   = (tamanho_gigante % 2 == 0);       // 1 se par, 0 se �mpar
            int mesmo = (ultimo_gigante == primeiro_fio); // 1 se mesmo estado

            char ornamento;
            if (par && mesmo)        ornamento = '@';
            else if (!par && mesmo)  ornamento = '#';
            else if (par && !mesmo)  ornamento = '$';
            else                     ornamento = '%';

            gigante[tamanho_gigante] = ornamento;
            tamanho_gigante++;
            gigante[tamanho_gigante] = '\0';

            // Anexa o fio
            strcpy(gigante + tamanho_gigante, S);
            tamanho_gigante += N;
        }
    }

    printf("%s\n", gigante);

    return 0;
}