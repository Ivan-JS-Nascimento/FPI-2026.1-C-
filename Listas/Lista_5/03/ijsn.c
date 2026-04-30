#include <stdio.h>
#include <stdlib.h>

// usei ia 100%, so dei uma estudada por cima.

// Função auxiliar para comparar notas (usada no qsort para mediana e moda)
int comparar(const void *a, const void *b) {
    float f1 = *(float *)a;
    float f2 = *(float *)b;
    if (f1 < f2) return -1;
    if (f1 > f2) return 1;
    return 0;
}

void imprimirRelatorio(float *notas, int n) {
    if (n <= 0) return;

    float soma = 0, maior, menor;
    int alunoMaior = 1, alunoMenor = 1;

    maior = menor = notas[0];

    for (int i = 0; i < n; i++) {
        soma += notas[i];
        if (notas[i] > maior) {
            maior = notas[i];
            alunoMaior = i + 1;
        }
        if (notas[i] < menor) {
            menor = notas[i];
            alunoMenor = i + 1;
        }
    }

    float media = soma / n;
    int acimaMedia = 0;
    for (int i = 0; i < n; i++) {
        if (notas[i] > media) acimaMedia++;
    }

    // Criar uma cópia para ordenar sem perder a ordem original dos alunos
    float *notasOrdenadas = malloc(n * sizeof(float));
    for (int i = 0; i < n; i++) notasOrdenadas[i] = notas[i];
    qsort(notasOrdenadas, n, sizeof(float), comparar);

    // Mediana
    float mediana;
    if (n % 2 != 0) {
        mediana = notasOrdenadas[n / 2];
    } else {
        mediana = (notasOrdenadas[(n / 2) - 1] + notasOrdenadas[n / 2]) / 2.0;
    }

    // Moda
    float modaValue = 0;
    int maxContagem = 0, contagemAtual = 0, modasEncontradas = 0;
    
    for (int i = 0; i < n; i++) {
        contagemAtual = 0;
        for (int j = 0; j < n; j++) {
            if (notasOrdenadas[j] == notasOrdenadas[i]) contagemAtual++;
        }
        if (contagemAtual > maxContagem) {
            maxContagem = contagemAtual;
            modaValue = notasOrdenadas[i];
        }
    }

    // Verificar se a moda é única
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (notasOrdenadas[j] == notasOrdenadas[i]) count++;
        }
        if (count == maxContagem) {
            if (notasOrdenadas[i] != modaValue || i == 0) {
                 // Lógica simples para detectar se há valores diferentes com a mesma contagem máxima
            }
        }
    }
    
    // Simplificação da moda: verificar se há empate na contagem máxima
    int empateModa = 0;
    float ultimaModaTestada = -1.0;
    for (int i = 0; i < n; i++) {
        int c = 0;
        if(notasOrdenadas[i] == ultimaModaTestada) continue;
        for(int j=0; j<n; j++) if(notasOrdenadas[j] == notasOrdenadas[i]) c++;
        if(c == maxContagem && c > 0 && notasOrdenadas[i] != modaValue) empateModa = 1;
        ultimaModaTestada = notasOrdenadas[i];
    }

    printf("Media: %.2f\n", media);
    printf("Maior nota: %.2f (aluno %d)\n", maior, alunoMaior);
    printf("Menor nota: %.2f (aluno %d)\n", menor, alunoMenor);
    printf("Acima da media: %d\n", acimaMedia);
    printf("Mediana: %.2f\n", mediana);
    
    if (maxContagem <= 1 || empateModa) printf("Moda: Nao ha moda unica\n");
    else printf("Moda: %.2f\n", modaValue);

    free(notasOrdenadas);
}

int main() {
    int n, k;
    float *notas = NULL;

    // Entrada inicial
    scanf("%d", &n);
    notas = (float *)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++) {
        scanf("%f", &notas[i]);
    }

    printf("Relatorio inicial\n");
    imprimirRelatorio(notas, n);

    // Adição de novas notas
    scanf("%d", &k);
    if (k > 0) {
        notas = (float *)realloc(notas, (n + k) * sizeof(float));
        for (int i = n; i < n + k; i++) {
            scanf("%f", &notas[i]);
        }
    }

    printf("\nRelatorio atualizado\n");
    imprimirRelatorio(notas, n + k);

    // O free final que discutimos!
    free(notas);

    return 0;
}