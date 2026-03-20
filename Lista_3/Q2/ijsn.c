#include <stdio.h>

int main() {

    int N;    // numero de clientes
    int X;    // clientes múltiplos de X compraram 1 lata
    int Y;    // número de clientes que constam no sistema com mais de 1 lata comprada
    int Wh, Wm, Z; // são respectivamente o horário no formato HH:MM e o número de latas compradas

    scanf("%d", &N);
    scanf("%d", &X);
    scanf("%d", &Y);

    int clientes[N+1], total;

    for(int i = 0; i < N+1; i++) {
        clientes[i] = 0;
    }

    if(X != 0){
        for(int i = X; i < N+1; i += X) {
            clientes[i] = 1;
        }
    }

    for (int i = 0; i < Y; i++) {
        scanf("%d:%d %d", &Wh, &Wm, &Z);
        int tempo_total_em_minutos = (Wh-7) * 60 + Wm;
        int posicao = (tempo_total_em_minutos / 3);
        clientes[posicao] = Z;
    }

    for(int i = 1; i <= N; i++) {
        total += clientes[i];
        if(total >= 50){
            int hh = 7, mm, tempo_total_em_minutos = i*3;
            if(tempo_total_em_minutos >= 60) {
                hh += tempo_total_em_minutos / 60;
                mm = tempo_total_em_minutos % 60;
            }else{
                mm = tempo_total_em_minutos;
            }

            if(clientes[i] == 1) {
                printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d lata.", i, hh, mm, clientes[i]);
            }else{
                printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.", i, hh, mm, clientes[i]);
            }
            return 0;
        }
    }

    if(50 - total == 1) {
        printf("Ainda nao foram vendidas latas suficientes. Falta %d lata.", 50 - total);
    }else{
        printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.", 50 - total);
    }

    return 0;   
}