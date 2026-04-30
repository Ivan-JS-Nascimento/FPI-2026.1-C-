#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ─────────────────────────────────────────
   ENUMERAÇÕES
───────────────────────────────────────── */
typedef enum {
    FOGO,
    AGUA,
    ELETRICIDADE,
    PLANTA
} TipoElemental;

typedef enum {
    SAIR               = 0,
    CADASTRAR_TREINADOR = 1,
    CADASTRAR_POKEMON   = 2,
    LISTA_CLASSIFICACAO = 3,
    REMOVER_TREINADOR   = 4,
    ATUALIZAR_POKEMON   = 5
} Comando;

/* ─────────────────────────────────────────
   ESTRUTURAS
───────────────────────────────────────── */
typedef struct {
    int         id;
    char        nome[100];
    TipoElemental tipo;
    int         xp;
    int         ataque;
    int         ordemRegistro; /* desempate na ordenação */
} Pokemon;

typedef struct {
    char     nome[100];
    char     cpf[20];
    int      idade;
    Pokemon *pokemons;
    int      qtdPokemons;
    int      nivel;
    int      ordemCadastro; /* desempate na ordenação */
} Treinador;

/* ─────────────────────────────────────────
   ESTADO GLOBAL
───────────────────────────────────────── */
typedef struct {
    Treinador *lista;
    int        qtd;
    int        contadorCadastro;   /* ordem global de cadastro de treinadores */
    int        contadorPokemon;    /* ordem global de registro de pokémons    */
} Sistema;

/* ─────────────────────────────────────────
   UTILITÁRIOS
───────────────────────────────────────── */
static TipoElemental parseTipo(const char *s) {
    /* aceita número ("0","1","2","3") ou nome */
    if (strcmp(s, "0") == 0 || strcmp(s, "Fogo")         == 0) return FOGO;
    if (strcmp(s, "1") == 0 || strcmp(s, "Agua")         == 0) return AGUA;
    if (strcmp(s, "2") == 0 || strcmp(s, "Eletricidade") == 0) return ELETRICIDADE;
    if (strcmp(s, "3") == 0 || strcmp(s, "Planta")       == 0) return PLANTA;
    return PLANTA; /* fallback */
}

static const char *tipoStr(TipoElemental t) {
    switch (t) {
        case FOGO:         return "Fogo";
        case AGUA:         return "Agua";
        case ELETRICIDADE: return "Eletricidade";
        case PLANTA:       return "Planta";
        default:           return "Desconhecido";
    }
}

static int calcForca(const Pokemon *p) {
    return 2 * p->xp + p->ataque;
}

static void recalcNivel(Treinador *t) {
    int nivel = 0;
    for (int i = 0; i < t->qtdPokemons; i++)
        nivel += calcForca(&t->pokemons[i]);
    t->nivel = nivel;
}

/* Encontra treinador pelo CPF; retorna índice ou -1 */
static int encontraTreinador(Sistema *sys, const char *cpf) {
    for (int i = 0; i < sys->qtd; i++)
        if (strcmp(sys->lista[i].cpf, cpf) == 0)
            return i;
    return -1;
}

/* Encontra pokémon pelo ID dentro de um treinador; retorna índice ou -1 */
static int encontraPokemon(Treinador *t, int id) {
    for (int i = 0; i < t->qtdPokemons; i++)
        if (t->pokemons[i].id == id)
            return i;
    return -1;
}

/* ─────────────────────────────────────────
   OPERAÇÕES (serão colocadas na struct de funções)
───────────────────────────────────────── */
static void op_cadastrarTreinador(Sistema *sys) {
    char nome[100], cpf[20];
    int  idade;
    scanf("%s %s %d", nome, cpf, &idade);

    if (encontraTreinador(sys, cpf) != -1)
        return; /* CPF já existe — ignora */

    sys->lista = realloc(sys->lista, (sys->qtd + 1) * sizeof(Treinador));
    Treinador *t = &sys->lista[sys->qtd];

    strcpy(t->nome, nome);
    strcpy(t->cpf,  cpf);
    t->idade         = idade;
    t->pokemons      = NULL;
    t->qtdPokemons   = 0;
    t->nivel         = 0;
    t->ordemCadastro = sys->contadorCadastro++;

    sys->qtd++;
}

static void op_cadastrarPokemon(Sistema *sys) {
    char cpf[20], nomePoke[100], tipoStr_[50];
    int  id, xp, ataque;
    scanf("%s %d %s %d %d %s", cpf, &id, nomePoke, &xp, &ataque, tipoStr_);

    int idx = encontraTreinador(sys, cpf);
    if (idx == -1) return;

    Treinador *t = &sys->lista[idx];
    if (encontraPokemon(t, id) != -1) return; /* ID duplicado — ignora */

    t->pokemons = realloc(t->pokemons, (t->qtdPokemons + 1) * sizeof(Pokemon));
    Pokemon *p  = &t->pokemons[t->qtdPokemons];

    p->id            = id;
    strcpy(p->nome, nomePoke);
    p->xp            = xp;
    p->ataque        = ataque;
    p->tipo          = parseTipo(tipoStr_);
    p->ordemRegistro = sys->contadorPokemon++;

    t->qtdPokemons++;
    recalcNivel(t);
}

/* Comparadores para qsort */
static int cmpPokemons(const void *a, const void *b) {
    const Pokemon *pa = (const Pokemon *)a;
    const Pokemon *pb = (const Pokemon *)b;
    int fa = calcForca(pa), fb = calcForca(pb);
    if (fb != fa) return fb - fa;                     /* maior força primeiro */
    return pa->ordemRegistro - pb->ordemRegistro;     /* desempate: mais antigo */
}

static int cmpTreinadores(const void *a, const void *b) {
    const Treinador *ta = (const Treinador *)a;
    const Treinador *tb = (const Treinador *)b;
    if (tb->nivel != ta->nivel) return tb->nivel - ta->nivel; /* maior nível primeiro */
    return ta->ordemCadastro - tb->ordemCadastro;             /* desempate: mais antigo */
}

static void op_listarClassificacao(Sistema *sys) {
    /* Cria cópias para ordenar sem alterar estado original */
    Treinador *copia = malloc(sys->qtd * sizeof(Treinador));
    memcpy(copia, sys->lista, sys->qtd * sizeof(Treinador));

    /* Copia os arrays de pokémons e os ordena */
    for (int i = 0; i < sys->qtd; i++) {
        Treinador *t = &copia[i];
        if (t->qtdPokemons > 0) {
            t->pokemons = malloc(t->qtdPokemons * sizeof(Pokemon));
            memcpy(t->pokemons, sys->lista[i].pokemons,
                   t->qtdPokemons * sizeof(Pokemon));
            qsort(t->pokemons, t->qtdPokemons, sizeof(Pokemon), cmpPokemons);
        }
    }
    qsort(copia, sys->qtd, sizeof(Treinador), cmpTreinadores);

    printf("Classificação atual\n");
    for (int i = 0; i < sys->qtd; i++) {
        Treinador *t = &copia[i];
        printf("T: %s, CPF: %s, Nivel: %d\n", t->nome, t->cpf, t->nivel);
        for (int j = 0; j < t->qtdPokemons; j++) {
            Pokemon *p = &t->pokemons[j];
            printf("  P: %d, %s, %d, %d, %s\n",
                   p->id, p->nome, p->xp, p->ataque, tipoStr(p->tipo));
        }
        if (t->qtdPokemons > 0) free(t->pokemons);
    }
    free(copia);
}

static void op_removerTreinador(Sistema *sys) {
    char cpf[20];
    scanf("%s", cpf);

    int idx = encontraTreinador(sys, cpf);
    if (idx == -1) return;

    free(sys->lista[idx].pokemons);

    /* Desloca os elementos seguintes */
    for (int i = idx; i < sys->qtd - 1; i++)
        sys->lista[i] = sys->lista[i + 1];

    sys->qtd--;
    sys->lista = realloc(sys->lista, sys->qtd * sizeof(Treinador));
}

static void op_atualizarPokemon(Sistema *sys) {
    char cpf[20], nomePoke[100], tipoStr_[50];
    int  id, xp, ataque;
    scanf("%s %d %s %d %d %s", cpf, &id, nomePoke, &xp, &ataque, tipoStr_);

    int idx = encontraTreinador(sys, cpf);
    if (idx == -1) return;

    Treinador *t   = &sys->lista[idx];
    int        pidx = encontraPokemon(t, id);
    if (pidx == -1) return;

    Pokemon *p = &t->pokemons[pidx];
    strcpy(p->nome, nomePoke);
    p->xp     = xp;
    p->ataque = ataque;
    p->tipo   = parseTipo(tipoStr_);

    recalcNivel(t);
}

static void op_sair(Sistema *sys) {
    for (int i = 0; i < sys->qtd; i++)
        free(sys->lista[i].pokemons);
    free(sys->lista);
    sys->lista = NULL;
    sys->qtd   = 0;
}

/* ─────────────────────────────────────────
   STRUCT DE FUNÇÕES (exigida pelo enunciado)
───────────────────────────────────────── */
typedef struct {
    void (*cadastrarTreinador)(Sistema *);
    void (*cadastrarPokemon)  (Sistema *);
    void (*listarClassificacao)(Sistema *);
    void (*removerTreinador)  (Sistema *);
    void (*atualizarPokemon)  (Sistema *);
    void (*sair)              (Sistema *);
} Operacoes;

/* ─────────────────────────────────────────
   MAIN
───────────────────────────────────────── */
int main(void) {
    Sistema sys = { .lista = NULL, .qtd = 0,
                    .contadorCadastro = 0, .contadorPokemon = 0 };

    Operacoes ops = {
        .cadastrarTreinador  = op_cadastrarTreinador,
        .cadastrarPokemon    = op_cadastrarPokemon,
        .listarClassificacao = op_listarClassificacao,
        .removerTreinador    = op_removerTreinador,
        .atualizarPokemon    = op_atualizarPokemon,
        .sair                = op_sair
    };

    int cmd;
    while (scanf("%d", &cmd) == 1) {
        Comando operacao = (Comando)cmd;

        switch (operacao) {
            case CADASTRAR_TREINADOR:  ops.cadastrarTreinador(&sys);   break;
            case CADASTRAR_POKEMON:    ops.cadastrarPokemon(&sys);     break;
            case LISTA_CLASSIFICACAO:  ops.listarClassificacao(&sys);  break;
            case REMOVER_TREINADOR:    ops.removerTreinador(&sys);     break;
            case ATUALIZAR_POKEMON:    ops.atualizarPokemon(&sys);     break;
            case SAIR:
                ops.sair(&sys);
                return 0;
            default:
                break;
        }
    }

    ops.sair(&sys);
    return 0;
}