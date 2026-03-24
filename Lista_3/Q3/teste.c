#include <stdio.h>
#include <string.h>

#define S 102

int main() {
    char palavras[S];
    // esse é pra ser a frase inteira

    fgets(palavras, S, stdin);

    int len = strlen(palavras)-1, totaldepares=0;
    if(len>0 && palavras[len] == '\n') palavras[len]='\0';// remove o \n do final
    char copy_palavras[len];

    // faz uma copia da string original
    for(int i = 0; i<len; i++){
        copy_palavras[i] = palavras[i];
    }

    // conoverta tudo para minusculo
    for(int i = 0 ; i<len ; i++) {
        if(palavras[i] >= 'A' && palavras[i] <= 'Z') palavras[i] = palavras[i] + 32;
    }

    int op=1, op2=1, comeco_p1 = 0, comeco_p2=0;
    // p1 é o indice da primeira palavra, o mesmo para p2

    while(op){ // loop principal
        char palavra1[len], palavra2[len];
        int tamanhop1 = 0, j=0, p1 = -1;

        if(comeco_p1 < len){

            // antes de pegar a primeira palavra, limpamos a array dela
            for(int i = 0; i<len;i++){
                palavra1[i]='0';
            }

            for(int i = comeco_p1 ; palavras[i]!=' ' && i < len ; i++){ // define primeira palavra
                if(p1==-1) p1 = i;
                comeco_p1 = i+2;
                comeco_p2 = i+2;

                palavra1[j] = palavras[i]; // guarda a palavra1
                j++;
                tamanhop1++;
            }

            while(op2){ // loop secundario
                int tamanhop2 = 0, cont = 0,p2 = -1;
                j=0;

                if(comeco_p2<len){

                    // antes de pegar a segunda palavra, limpamos a array dela
                    for(int i = 0; i<len;i++){
                        palavra2[i]='0';
                    }

                    for(int i = comeco_p2 ; palavras[i]!=' ' && i < len ; i++){ // define segunda palavra
                        if(p2==-1) p2 = i;
                        comeco_p2 = i+2;

                        palavra2[j] = palavras[i]; // guarda a palavra2
                        j++;
                        tamanhop2++;
                    }

                    if(tamanhop1 == tamanhop2 && tamanhop1!=0){ //? lembre-se

                        // ==================== verificar se é anagrama =====================
                        for(int i = 0; palavra1[i] != '0' ; i++){ 
                            for(int j = 0; palavra1[j] != '0' ; j++){
                                if(palavra1[i] == palavra2[j]){
                                    cont++;
                                    palavra2[j] = '1';
                                    break;
                                }
                            }
                        }

                        // ============= System.out.prints ==================
                        if(cont == tamanhop1){
                            if(totaldepares==0) printf("Pares de anagramas encontrados:\n");
                            totaldepares++;

                            for(int i = p1 ; copy_palavras[i]!=' ' && i<len ; i++){
                                printf("%c", copy_palavras[i]);
                            }

                            printf(" e ");

                            for(int i = p2 ; copy_palavras[i]!=' ' && i<len ; i++){
                                printf("%c", copy_palavras[i]);
                            }

                            printf("\n");

                        }
                    }

                }else{
                    break;
                }
            }

        }else{
            op=0;
        }
    }

    if(totaldepares!=0) printf("\nTotal de pares: %d\n", totaldepares);
    else printf("Nao existem anagramas na frase.\n");

    return 0;
}
