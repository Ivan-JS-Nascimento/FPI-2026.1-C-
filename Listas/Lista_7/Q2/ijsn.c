#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;     // Atk: Dano Base   | Def: Blindagem Fixa | Utl: Recup. Base
    int atrib2;     // Atk: Custo Ener. | Def: Bônus de Slot   | Utl: Multiplicador
    
    // Função Modular: deve ser atribuída conforme o tipo do sistema.
    // m: ponteiro para o mecha dono do sistema.
    // slot: o índice da posição de entrada deste sistema no array sistemas[]
    // input: o dano base enviado pelo Wintermute para o combate.
    // output: onde deve ser gravado o resultado final da operação.
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;                // Identificador único (0 até N-1)
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;       // Contexto de dano enviado pelo Comando
    SubSistema sistemas[]; // O Flexible Array Member (FAM)
};
// ============================================================================================
void defesa(Mecha *m, int slot, int input, int *output){
    int dano_sofrido = input - m->sistemas[slot].atrib1 - (slot * m->sistemas[slot].atrib2);
    if(dano_sofrido < 0) dano_sofrido = 0;
    *output = dano_sofrido;
}
void utilidade(Mecha *m, int slot, int input, int *output){
    int recuperar = m->sistemas[slot].atrib1 + (slot * m->sistemas[slot].atrib2);
    m->energia_atual += recuperar;
    *output = recuperar;
}
void ataque(Mecha *m, int slot, int input, int *output){
    if(m->energia_atual < m->sistemas[slot].atrib2){
        *output = 0; // energia insuficiente para ativar o sistema, logo dano é 0.
    } else {
        int dano_causado =  m->sistemas[slot].atrib1 + m->energia_atual + slot - input;
        m->energia_atual -= m->sistemas[slot].atrib2; // desconta o custo de energia do ataque
        *output = dano_causado;
    }
}
// ============================================================================================

// void printar(Mecha *m){ // apenas para debug
//     printf("ID: %d | ", m->id);
//     printf("Modelo: %s | ", m->modelo);
//     printf("Energia Atual: %d | ", m->energia_atual);
//     printf("Número de Sistemas: %d\n", m->num_sistemas);
//     for(int i = 0; i < m->num_sistemas; i++){
//         printf("Sistema %d: %s ", i, m->sistemas[i].nome);
//     }
//     printf("\n");
// }
// ============================================================================================
int main(){
    int N;
    scanf("%d", &N);

    Mecha *equadrao[N];


    // === Fase de Montagem ===
    for(int i = 0; i < N; i++){
        // recebe um mecha por vez
        int id, energia, num_sistemas, valor_wintermute;
        char modelo[50];

        scanf("%d %s %d %d", &id, modelo, &energia, &num_sistemas);

        Mecha *m = malloc(sizeof(Mecha) + sizeof(SubSistema) * num_sistemas);

        m->id = id;
        strcpy(m->modelo, modelo);
        m->energia_atual = energia;
        m->num_sistemas = num_sistemas;

        // recebe os sistemas de cada mecha
        for(int j = 0; j < num_sistemas; j++){
            char nome[30] , tipo[2];
            int atrib1, atrib2;
            scanf("%s %s %d %d", tipo, nome, &atrib1, &atrib2);

            m->sistemas[j].atrib1 = atrib1;
            m->sistemas[j].atrib2 = atrib2;
            strcpy(m->sistemas[j].nome, nome);

            // definindo qual funçao cada sistema deve executar conforme seu tipo.
            if(tipo[0] == 'A') m->sistemas[j].subrotina = ataque;
            if(tipo[0] == 'D') m->sistemas[j].subrotina = defesa;
            if(tipo[0] == 'U') m->sistemas[j].subrotina = utilidade;
        }

        scanf("%d", &valor_wintermute);
        m->valor_wintermute = valor_wintermute;

        // armazena o endereço do mecha no esquadrao.
        // lebrar: assim que m e redeclarado
        //  cada iteração do for tem um m diferente, apontando para um endereco doferente.
        equadrao[m->id] = m;
    }

    // === Fase de Combate ===
    puts("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]");
    for(int i=0 ; i<N ; i++){
        Mecha *m = equadrao[i];
        int resultado = 0;
        int input = m->valor_wintermute;

        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", m->id, m->modelo, m->energia_atual);

        for(int j=0 ; j<m->num_sistemas ; j++){
            if(m->sistemas[j].subrotina == defesa){
                m->sistemas[j].subrotina(m, j, input, &resultado);
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->sistemas[j].nome, resultado);
            }
        }
        resultado = 0;
        for(int j=0 ; j<m->num_sistemas ; j++){
            if(m->sistemas[j].subrotina == utilidade){
                m->sistemas[j].subrotina(m, j, input, &resultado);
                printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->sistemas[j].nome, m->energia_atual);
            }
        }
        resultado = 0;
        for(int j=0 ; j<m->num_sistemas ; j++){
            if(m->sistemas[j].subrotina == ataque){
                m->sistemas[j].subrotina(m, j, input, &resultado);
                if(resultado != 0) printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", m->sistemas[j].nome, resultado, m->energia_atual);
                else printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[j].nome);
            }
        }
        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        puts("-----------------------------------------");
    }
    puts("Esquadrao pronto para o combate.");

    // for(int i = 0; i < N; i++){
    //     printar(equadrao[i]);
    // } 

    for(int i = 0; i < N; i++){
        free(equadrao[i]);
    }

    return 0;
}