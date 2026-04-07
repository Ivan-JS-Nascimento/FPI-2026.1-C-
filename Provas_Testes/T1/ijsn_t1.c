// Teste 1: O Código de Monalisa / 09/03/2026

#include <stdio.h>

int main(){
    int V1, V2, V3, D;
    int d1, d2, caminhoDireto, caminhop2, escolhido;

    scanf("%d %d %d %d", &V1, &V2, &V3, &D);
    d1 = (int) D / 10;
    d2 = D - d1*10;

    caminhoDireto = V1 + V3;
    caminhop2 = V1 + V2 + V3;
    

    if( d1 > d2){//• Se d1 > d2: o caminho direto recebe bônus de (d1 - d2) pontos.
        caminhoDireto += d1 - d2;

    } else if (d2 > d1) {//• Se d2 > d1: o caminho por P2 recebe bônus de (d2 - d1) pontos.
        caminhop2 += d2 - d1;

    } else {//• Se d1 = d2: ambos os caminhos recebem bônus de (d1 + d2) pontos.
        caminhoDireto += d1 + d2;
        caminhop2 += d1 + d2;
    }


    if( caminhoDireto > caminhop2 ){
        printf("Caminho: direto.");
        escolhido = caminhoDireto;
    } else if( caminhop2 > caminhoDireto ){
        printf("Caminho: P2.");
        escolhido = caminhop2;
    } else {
        printf("Caminho: P2.");
        escolhido = caminhop2;
    }

    if( escolhido > 30){
        puts(" Xupenio aprova! Nível: ELITE.");

    } else if( escolhido >= 10){
        puts(" Boa caminhada! Nível: SÓLIDO.");

    }else if( escolhido >= 0){
        puts(" Passou por pouco. Nível: BÁSICO.");

    } else {
        puts(" Xupenio reprova. Nível: CRÍTICO.");

    }

    return 0;
}