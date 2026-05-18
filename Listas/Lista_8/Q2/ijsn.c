#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct{
    uint32_t sensor_id  : 10;  // bits  0-9   → 0 a 1023
    uint32_t status     :  3;  // bits 10-12  → 0 a 7
    uint32_t bateria    :  1;  // bit  13     → 0 ou 1
    int32_t  temp       : 12;  // bits 14-25  → com sinal! (int32_t)
    uint32_t paridade   :  6;  // bits 26-31  → verificação
} CamposPacote;

typedef union{
    uint32_t raw;
    CamposPacote campos;
} Pacote;


void imprimir_pacote(const Pacote *p, int num){
    printf("Pacote [%d] - Dado Bruto: 0x%08X\n", num, p->raw);
    printf("  ID do Sensor : %u\n",   p->campos.sensor_id);
    printf("  Status       : %u\n",   p->campos.status);
    printf("  Bateria Baixa: %s\n",   p->campos.bateria ? "SIM (ALERTA)" : "Nao");
    printf("  Temperatura  : %d graus\n", p->campos.temp);
    printf("----------------------------------------------\n");
}


int main(){
    int capacidade = 2;
    int quantidade = 0;

    Pacote *vetor = malloc(capacidade * sizeof(Pacote));

    if(!vetor){ // ======================== ERRO
        printf("Erro: falha ao alocar memória inicial\n");
        return 1;
    }

    uint32_t entrada;

    while(scanf("%x", &entrada) == 1 && entrada != 0){
        if(quantidade == capacidade){
            capacidade *= 2;
            Pacote *temporario = realloc(vetor, capacidade * sizeof(Pacote));
            if(!temporario){ // ======================== ERRO
                printf("Erro: falha ao realocar memória\n");
                free(vetor);
                return 1;
            }
            vetor = temporario;
        }
        vetor[quantidade].raw = entrada;
        quantidade++;
    }

    for(int i=0; i<quantidade; i++){
        imprimir_pacote(&vetor[i],i+1);
    }

    free(vetor);
    return 0;
}
