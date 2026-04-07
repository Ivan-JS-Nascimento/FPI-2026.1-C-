#include <stdio.h>

/*
- usei ia para gerar o codigo.
*/

int main() {
    int X, N; // X = numero alvo, N = numero de canais
    scanf("%d %d", &X, &N);

    int best_canal = -1;   // canal com o termo mais proximo de X
    int best_minuto = -1;  // minuto em que esse termo aparece
    long long best_term = -1; // valor do termo mais proximo
    long long best_dist = -1; // distancia do melhor termo ate X

    int canal;
    for (canal = 1; canal <= N; canal++) { // para cada canal
        long long f1, f2;
        scanf("%lld %lld", &f1, &f2); // f1 = primeiro termo, f2 = segundo termo da sequencia de fibonacci do canal

        long long prev = f1, curr = f2; // termos anteriores para calcular o proximo
        int minuto = 1;

        // inicializa o mais proximo com o primeiro termo
        long long close_term = f1;
        long long close_dist = f1 - X;
        if (close_dist < 0) close_dist = -close_dist; // valor absoluto da distancia
        int close_min = 1;

        // verifica se o segundo termo e mais proximo de X
        long long d = curr - X;
        if (d < 0) d = -d;
        if (d < close_dist) {
            close_dist = d;
            close_term = curr;
            close_min = 2;
        }

        // percorre os proximos termos da sequencia ate o 200 ou ate ultrapassar 2 bilhoes
        int i;
        for (i = 3; i <= 200; i++) {
            long long next = prev + curr; // proximo termo de fibonacci
            d = next - X;
            if (d < 0) d = -d;
            if (d < close_dist) { // atualiza se esse termo e mais proximo de X
                close_dist = d;
                close_term = next;
                close_min = i;
            }
            prev = curr;
            curr = next;
            if (next > 2000000000LL) break; // para se ultrapassar o limite
        }

        // atualiza o melhor canal se esse e mais proximo (ou igualmente proximo)
        if (best_dist == -1 || close_dist < best_dist || (close_dist == best_dist)) {
            best_dist = close_dist;
            best_canal = canal;
            best_minuto = close_min;
            best_term = close_term;
        }
    }

    // calcula a soma dos digitos do melhor termo encontrado
    long long temp = best_term;
    if (temp < 0) temp = -temp; // garante valor positivo
    int digit_sum = 0;
    while (temp > 0) {
        digit_sum += temp % 10; // pega o ultimo digito e acumula
        temp /= 10;             // remove o ultimo digito
    }

    // exibe resultado com ou sem VIP dependendo da soma dos digitos
    if (digit_sum > 10) {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", best_canal, best_minuto);
    } else {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP não vai rolar :(\n", best_canal, best_minuto);
    }

    return 0;
}