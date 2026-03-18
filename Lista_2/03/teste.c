#include <stdio.h>

int main() {
    int X, N;
    scanf("%d", &X);
    scanf("%d", &N);

    int best_canal = -1;
    int best_minuto = -1;
    long long best_term = -1;
    long long best_dist = -1;

    int canal;
    for (canal = 1; canal <= N; canal++) {
        long long f1, f2;
        scanf("%lld %lld", &f1, &f2);

        long long prev = f1, curr = f2;
        int minuto = 1;
        long long close_term = f1;
        long long close_dist = f1 - X;
        if (close_dist < 0) close_dist = -close_dist;
        int close_min = 1;

        long long d = curr - X;
        if (d < 0) d = -d;
        if (d < close_dist) {
            close_dist = d;
            close_term = curr;
            close_min = 2;
        }

        int i;
        for (i = 3; i <= 200; i++) {
            long long next = prev + curr;
            d = next - X;
            if (d < 0) d = -d;
            if (d < close_dist) {
                close_dist = d;
                close_term = next;
                close_min = i;
            }
            prev = curr;
            curr = next;
            if (next > 2000000000LL) break;
        }

        if (best_dist == -1 || close_dist < best_dist || (close_dist == best_dist)) {
            best_dist = close_dist;
            best_canal = canal;
            best_minuto = close_min;
            best_term = close_term;
        }
    }

    long long temp = best_term;
    if (temp < 0) temp = -temp;
    int digit_sum = 0;
    while (temp > 0) {
        digit_sum += temp % 10;
        temp /= 10;
    }

    if (digit_sum > 10) {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", best_canal, best_minuto);
    } else {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP não vai rolar :(\n", best_canal, best_minuto);
    }

    return 0;
}