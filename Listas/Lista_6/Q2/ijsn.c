#include <stdio.h>
#include <stdlib.h>

typedef enum{
    FOGO,
    AGUA,
    ELETRICIDADE,
    PLANTA
}TipoElemento;

typedef struct{
    int             id;  // único para cada treinador
    char            nome[100];
    TipoElemento    tipo;
    int             xp;
    int             ataque;
}Pokemon;

typedef struct{
    char            nome[100];
    char            cpf[20];
    int             idade;
    Pokemon         *pokemon;
    int             nivel;
} Treinador;






// -------------  MAIN -------------
int main(){
    



    return 0;
}