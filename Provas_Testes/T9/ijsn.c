// fig11_04.c — Cria o arquivo de acesso aleatório
#include <stdio.h>

struct clientData {
    int account;
    char lastName[15];
    char firstName[10];
    double balance;
};

int main(void) {
    FILE *cfPtr = NULL;

    // "wb" = write binary (escrita em binário)
    if ((cfPtr = fopen("accounts.dat", "wb")) == NULL) {
        puts("Arquivo não pôde ser aberto.");
        return 1;
    }

    // Registro em branco para inicializar o arquivo
    struct clientData blankClient = {0, "", "", 0.0};

    // Escreve 100 registros em branco
    for (int i = 1; i <= 100; i++) {
        fwrite(&blankClient, sizeof(struct clientData), 1, cfPtr);
        //       ^endereço    ^tamanho fixo em bytes   ^qtd  ^arquivo
    }

    fclose(cfPtr);
    puts("Arquivo criado com 100 registros em branco!");
}