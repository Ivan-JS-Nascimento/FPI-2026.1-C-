#include <stdio.h>
#include <stdlib.h>

typedef struct{
    unsigned char erro    : 1;
    unsigned char modo    : 3;
    unsigned char leitura : 4;
} CamposSensor;

typedef union{
    unsigned char rawByte;
    CamposSensor campos;
}RegistroSensor;

void decodificador(unsigned char valor){
    RegistroSensor registro;

    registro.rawByte = valor;
    printf("Byte bruto: %d | Erro: %d | Modo: %d | Leitura: %d\n",
        registro.rawByte,
        registro.campos.erro,
        registro.campos.modo,
        registro.campos.leitura
    );

}

int main(){

    decodificador(0);
    decodificador(255);
    decodificador(162);
    decodificador(85);
    decodificador(200);
    return 0;
}