#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    float sepal_length;
    float sepal_width;
    float petal_length;
    float petal_width;
    char species[50];
} Flor;

void limpar_char(char *c, int tamanho){
    for(int i=0; i<tamanho; i++){
        c[i] = '\0';
    }
}

int main(){
    int N = 2;
    //scanf("%d", &N);
    for(int i=0; i<N; i++){ // loop pra cada arquivo
        int quantidade = 0, tamanho = 2;
        Flor *fulo = malloc(tamanho * sizeof(Flor));
        if(fulo == NULL) return 1;
        
        // linha de leitura do arquivo e nome do arquivo
        char linha[200], nome_file[20]; 

        sprintf(nome_file, "iris%d.csv", i+1);
        FILE *file = fopen(nome_file, "r");

        if(file == NULL){
            free(fulo);
            return 1;
        }

        int x = 0; // apenas para pular a primeira linha do arquivo
        printf("Arquivo: %s\n", nome_file);
        while (fgets(linha, sizeof(linha), file) != NULL){
            printf("%s", linha);
            if(x!=0){
                if(quantidade == tamanho){
                    Flor *temp = realloc(fulo, (tamanho+=2) * sizeof(Flor));
                    if(temp == NULL){
                        fclose(file);
                        free(fulo);
                        return 1;
                    }
                    fulo = temp;
                }
                // gurardar os dados do arquivo na struct
                sscanf(linha, "%f,%f,%f,%f,%s", 
                    &fulo[quantidade].sepal_length, 
                    &fulo[quantidade].sepal_width, 
                    &fulo[quantidade].petal_length, 
                    &fulo[quantidade].petal_width, 
                    fulo[quantidade].species);
                quantidade++;
            }
            x++;
            limpar_char(linha, sizeof(linha));
        }
        printf("\n");// por causa da ultima linha do aquivo que não tem \n(pelo que eu entendi)
        // calcular medias
        float media_sepal_length = 0, media_sepal_width = 0, media_petal_length = 0, media_petal_width = 0;
        int contador[200]; // contador para cada espécie, considerando que não tem mais que 200 espécies diferentes
        for(int j=0; j<200; j++){
            contador[j] = 0;
        }
        int index = 0;
        for(int j=0; j<quantidade; j++){
            contador[j] = 0;
            for(int k=0; k<quantidade; k++){
                if(strcmp(fulo[j].species, fulo[k].species) == 0){
                    contador[j]++;
                }
            }
            // verificar se o contador da espécie atual é maior que o contador da espécie mais frequente encontrada até agora, ou se é igual e a espécie atual é alfabeticamente menor
            if(contador[j] > contador[index] || (contador[j] == contador[index] && strcmp(fulo[j].species, fulo[index].species) < 0)) index = j;

            media_sepal_length += fulo[j].sepal_length;
            media_sepal_width  += fulo[j].sepal_width;
            media_petal_length += fulo[j].petal_length;
            media_petal_width  += fulo[j].petal_width;
        }
        if(quantidade > 0){
            media_sepal_length /= quantidade;
            media_sepal_width  /= quantidade;
            media_petal_length /= quantidade;
            media_petal_width  /= quantidade;
        }
        fclose(file);
        file = fopen(nome_file, "a");
        fprintf(file, "\n\n");
        fprintf(file, "Média Sepal Length: %.2f\n", media_sepal_length);
        fprintf(file, "Média Sepal Width: %.2f\n", media_sepal_width);
        fprintf(file, "Média Petal Length: %.2f\n", media_petal_length);
        fprintf(file, "Média Petal Width: %.2f\n", media_petal_width);
        fprintf(file, "Moda species: %s\n", fulo[index].species);
        fclose(file);
        free(fulo);
    }
    return 0;
}