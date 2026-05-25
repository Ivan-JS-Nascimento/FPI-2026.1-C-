#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct{
    uint64_t tipo          : 2;
    uint64_t id_subsistema : 6;
    uint64_t eixo          : 2;
    uint64_t temperatura   : 10;
    uint64_t velocidade_a  : 18;
    uint64_t paridade      : 26;
} Navegacao;

typedef struct{
    uint64_t tipo            : 2;
    uint64_t id_subsistema   : 6;
    uint64_t tensao_painel   : 12;
    uint64_t corrente_consumo: 12;
    uint64_t status_baterias : 4;
    uint64_t checksum        : 28;
} Energia;

typedef struct{
    uint64_t tipo         : 2;
    uint64_t id_subsistema: 6;
    uint64_t codigo_erro  : 8;
    uint64_t criticidade  : 3;
    uint64_t timestamp    : 20;
    uint64_t padding      : 25;
} AlertaSistema;


typedef union{
    uint64_t      raw;
    Navegacao     N;
    Energia       E;
    AlertaSistema A;
} Pacotes;

// -------------------------------------

typedef struct{
    uint64_t tipo        : 2;
    uint64_t nulo1       : 14;
    uint64_t criticidade : 3;
    uint64_t nulo2       : 20;
    uint64_t nulo3       : 25;
}Seletor;
typedef union{
    uint64_t   raw;
    Seletor    S;
} Filtro;

// -------------------------------------

void imprimir(const Pacotes *P, int indice){
    printf("[Registro %d] RAW: 0x%016llX\n", indice, P->raw);
    if(P->A.tipo == 0){ 
        printf("-> Tipo: %s", "Navegação\n");
        printf("-> ID do Subsistema Origem: %d\n", P->N.id_subsistema);
        printf("-> Temperatura: %d°C\n", P->N.temperatura);
        printf("-> Velocidade Angular: %d rad/s\n", P->N.velocidade_a);
        //0=X, 1=Y, 2=Z, 3=Calibração
        if(P->N.eixo == 0) printf("-> Eixo: X\n");
        if(P->N.eixo == 1) printf("-> Eixo: Y\n");
        if(P->N.eixo == 2) printf("-> Eixo: Z\n");
        if(P->N.eixo == 3) printf("-> Eixo: Calibração\n");
    } else if(P->A.tipo == 1){
        printf("-> Tipo: %s", "Energia\n");
        printf("-> ID do Subsistema Origem: %d\n", P->E.id_subsistema);
        printf("-> Tensão do Painel: %d mV\n", P->E.tensao_painel);
        printf("-> Corrente de Consumo: %d mA\n", P->E.corrente_consumo);
        if(P->E.status_baterias == 0){
            printf("-> Status da Baterias: OK\n");
        }else{
            printf("-> Status da Baterias: Falha no(s) quadrante(s) ");
            if(P->E.status_baterias == 1) printf("0\n");      // 0001
            if(P->E.status_baterias == 2) printf("1\n");      // 0010
            if(P->E.status_baterias == 3) printf("0 1\n");    // 0011
            if(P->E.status_baterias == 4) printf("2\n");      // 0100
            if(P->E.status_baterias == 5) printf("0 2\n");    // 0101
            if(P->E.status_baterias == 6) printf("1 2\n");    // 0110
            if(P->E.status_baterias == 7) printf("0 1 2\n");  // 0111
            if(P->E.status_baterias == 8) printf("3\n");      // 1000
            if(P->E.status_baterias == 9) printf("0 3\n");    // 1001
            if(P->E.status_baterias ==10) printf("1 3\n");    // 1010
            if(P->E.status_baterias ==11) printf("0 1 3\n");  // 1011
            if(P->E.status_baterias ==12) printf("2 3\n");    // 1100
            if(P->E.status_baterias ==13) printf("0 2 3\n");  // 1101
            if(P->E.status_baterias ==14) printf("1 2 3\n");  // 1110
            if(P->E.status_baterias ==15) printf("0 1 2 3\n");// 1111
        }
    } else if(P->A.tipo == 2){
        printf("-> Tipo: %s", "Alerta do Sistema\n");
        printf("-> ID do Subsistema Origem: %d\n", P->A.id_subsistema);
        printf("-> Código do Erro: %d\n", P->A.codigo_erro);
        if(P->A.criticidade == 0) printf("-> Nível de Criticidade: Info");
        if(P->A.criticidade == 1) printf("-> Nível de Criticidade: Warning");
        if(P->A.criticidade == 2) printf("-> Nível de Criticidade: Severe");
        if(P->A.criticidade == 3) printf("-> Nível de Criticidade: Fatal");
        printf("\n");
        printf("-> Timestamp Relativo: %d ms\n", P->A.timestamp);
    }
}

int main(){
    //printf("%d\n",sizeof(Pacotes));
    //printf("%d\n",sizeof(Seletor));
    int capacidade = 4;
    int tamanho = 0;
    int quant_crit_sever_fatal = 0;
    uint64_t barramento;

    Pacotes *vetor = malloc(capacidade * sizeof(Pacotes));

    if(!vetor){
        puts("erro no malloc");
        return 0;
    }

    while(scanf("%llX", &barramento) != 0 && barramento != 0){
        //printf("\nprintf: 0x%016llX", barramento);
        Filtro F;
        F.raw = barramento;
        // printf("\nFiltro: \n");
        // printf("raw: 0x%016llX\n", F.raw);
        // printf("S.tipo: %d\n", F.S.tipo);
        // printf("S.criticidade: %d\n", F.S.criticidade);
        if(F.S.tipo == 3 || (F.S.tipo == 2 && F.S.criticidade >= 4)){
            //printf("1-----------\n");
            // 2.2 Filtragem de Pacotes
        } else {
            //printf("2-----------\n");
            if(capacidade == tamanho){
                //printf("\nRealocando...\n");
                capacidade+=4;
                Pacotes *temporario = realloc(vetor, capacidade * sizeof(Pacotes));
                if(!temporario){
                    puts("erro no realloc");
                    free(vetor);
                    return 0;
                }
                vetor = temporario;
            }

            vetor[tamanho].raw = barramento;
            tamanho++;
            //printf("Tamanho: %d\n", tamanho);
            //printf("vetor[%d]: 0x%016llX\n", tamanho-1, vetor[tamanho-1].raw);
        }
    }

    puts("RELATÓRIO DE TELEMETRIA - CUBESAT");
    int soma_media_t = 0, cont_t = 0;
    int soma_media_c = 0, cont_c = 0;
    float media_t = 0, media_c = 0;
    for(int i=0; i<tamanho ;i++){
        imprimir(&vetor[i], i+1);
        if(vetor[i].A.tipo == 0){
            soma_media_t += vetor[i].N.temperatura;
            cont_t++;
        }
        if(vetor[i].A.tipo == 1){
            soma_media_c += vetor[i].E.corrente_consumo;
            cont_c++;
        }
        if(vetor[i].A.tipo == 2 && (vetor[i].A.criticidade == 2 || vetor[i].A.criticidade == 3)){
            quant_crit_sever_fatal++;
        }
    }

    printf("\nESTATÍSTICAS CONSOLIDADAS\n");
    printf("- Total de pacotes válidos processados: %d\n", tamanho);
    if(cont_t != 0) media_t = soma_media_t / cont_t;
    if(cont_c != 0) media_c = soma_media_c / cont_c;
    printf("- Média de Temperatura Externa (Tipo 0): %.2f°C\n", media_t);
    printf("- Média de Corrente de Consumo (Tipo 1): %.2f mA\n", media_c);
    printf("- Alertas Críticos Detectados (Severe/Fatal): %d", quant_crit_sever_fatal);


    free(vetor);
    return 0;
}