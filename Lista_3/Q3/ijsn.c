#include <stdio.h>
#include <string.h>

int main() {
    char s[102];
    fgets(s, sizeof(s), stdin);

    // Converter tudo para minúsculo
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] + 32;
        }
    }

    // Guardar início e tamanho de cada palavra (dois vetores 1D paralelos)
    int inicio[50];
    int tamanho[50];
    int num_palavras = 0;

    int i = 0;
    while (s[i] != '\0') {
        // Pula não-letras
        if (s[i] < 'a' || s[i] > 'z') {
            i++;
            continue;
        }
        // Achou início de uma palavra
        inicio[num_palavras] = i;
        int tam = 0;
        while (s[i] >= 'a' && s[i] <= 'z') {
            tam++;
            i++;
        }
        tamanho[num_palavras] = tam;
        num_palavras++;
    }

    // Comparar pares
    int pares = 0;
    char resultado[5000];
    resultado[0] = '\0';

    for (int a = 0; a < num_palavras; a++) {
        for (int b = a + 1; b < num_palavras; b++) {

            // Tamanhos diferentes: não podem ser anagramas
            if (tamanho[a] != tamanho[b]) continue;

            // Contar frequência de letras da palavra A
            int freq[26];
            for (int k = 0; k < 26; k++) freq[k] = 0;
            for (int k = 0; k < tamanho[a]; k++) {
                freq[s[inicio[a] + k] - 'a']++;
            }

            // Subtrair frequência da palavra B
            for (int k = 0; k < tamanho[b]; k++) {
                freq[s[inicio[b] + k] - 'a']--;
            }

            // Se todas as frequências são zero, é anagrama
            int anagrama = 1;
            for (int k = 0; k < 26; k++) {
                if (freq[k] != 0) {
                    anagrama = 0;
                    break;
                }
            }

            if (anagrama) {
                pares++;
                // Concatena "p1 e p2\n" no resultado
                int pos = strlen(resultado);
                for (int k = 0; k < tamanho[a]; k++) {
                    resultado[pos++] = s[inicio[a] + k];
                }
                resultado[pos++] = ' ';
                resultado[pos++] = 'e';
                resultado[pos++] = ' ';
                for (int k = 0; k < tamanho[b]; k++) {
                    resultado[pos++] = s[inicio[b] + k];
                }
                resultado[pos++] = '\n';
                resultado[pos] = '\0';
            }
        }
    }

    if (pares == 0) {
        printf("Nao existem anagramas na frase.\n");
    } else {
        printf("Pares de anagramas encontrados:\n");
        printf("%s", resultado);
        printf("\nTotal de pares: %d\n", pares);
    }

    return 0;
}