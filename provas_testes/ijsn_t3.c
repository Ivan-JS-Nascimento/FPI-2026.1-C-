// Teste 3 - 23/03/2026 - Palavras Vizinhas

#include <stdio.h>
#define SIZE 102

int main(){
    char palavras[SIZE], clonepalavras[SIZE];
    int tootal_pares = 0, w=0;
    fgets(palavras, SIZE, stdin);
    
    int a=0;
    for(int i = 0; palavras[i] != '\n' ;i++){ // converter para minusculo
        clonepalavras[i] = palavras[i];
        if(palavras[i] >= 'A' && palavras[i] <= 'Z'){
            palavras[i] += 32;
        }
        a++;
    }

    clonepalavras[a] = 0;

    for(int e = 0; palavras[e] != '\n' && palavras[e] != '\000' && e<102 ;e++){ // loop principal
        char p1[50], p2[50];
        for(int j = 0; j < 50 ; j++){// limpa p1 e p2
            p1[j] = '0';
            p2[j] = '0';
        }
        int t1=0, t2=0, j=0, x, loc1=-1, loc2=-1;
        //j=para contar o tamanho, x=para começar a partir do proximo


        for(int i = w; palavras[i] != ' ' && palavras[i] != '\n' && palavras[i] != '\000' && i<102 ;i++){ // pega a primeira palavra
            if(palavras[i] >= 'a' && palavras[i] <= 'z'){
                if(loc1==-1) loc1 = i;
                p1[j] = palavras[i];
                j++;
            }
            t1 = j;
            x = i+2;
            w = i+2;
        }

        if(t1 != 0){

            for(int i = 0; palavras[i] != '\n' && palavras[i] != '\000' && i<102 ;i++){ // loop secundario
                for(int j = 0; j < 50 ; j++){
                    p2[j] = '0';
                }
                loc2 = -1;
                t2 = 0;
                j = 0;

                for(int d = x; palavras[d] != ' ' && palavras[d] != '\n' && palavras[d] != '\000' && d <102;d++){ // pega a segunda palavra
                    if(palavras[d] >= 'a' && palavras[d] <= 'z'){ // limpa p2
                        if(loc2==-1) loc2 = d;
                        p2[j] = palavras[d];
                        j++;
                    }
                    t2 = j;
                    x = d+2;
                }

                if(t2!=0){

                    char sp1[50], sp2[50];
                    for(int y = 0; y<50 ;y++){
                        sp1[y] = p1[y];
                        sp2[y] = p2[y];
                    }

                    if(t1==t2){ //Substituição
                        int cont = 0;

                        for(int e = 0; sp1[e] != '0' ; e++){ // conta as letras iguais
                            if(sp1[e] == sp2[e]){
                                cont++;
                            }
                        }

                        if(cont == t1){
                            if(tootal_pares == 0){
                                printf("Pares de palavras vizinhas encontrados:\n");
                            }
                            for(int v=loc1; clonepalavras[v]!= ' ' && clonepalavras[v] != '\n' && clonepalavras[v] != '\000'; v++){
                                printf("%c", clonepalavras[v]);
                            }
                            printf(" e ");
                            for(int v=loc2; clonepalavras[v]!= ' ' && clonepalavras[v] != '\n' && clonepalavras[v] != '\000'; v++){
                                printf("%c", clonepalavras[v]);
                            }
                            printf("\n");
                            tootal_pares++;

                        }else if(cont == t1-1){
                            if(tootal_pares == 0){
                                printf("Pares de palavras vizinhas encontrados:\n");
                            }
                            for(int v=loc1; clonepalavras[v]!= ' ' && clonepalavras[v] != '\n' && clonepalavras[v] != '\000'; v++){
                                printf("%c", clonepalavras[v]);
                            }
                            printf(" e ");
                            for(int v=loc2; clonepalavras[v]!= ' ' && clonepalavras[v] != '\n' && clonepalavras[v] != '\000'; v++){
                                printf("%c", clonepalavras[v]);
                            }
                            printf("\n");
                            tootal_pares++;
                            
                        }

                    }else if(t1 == t2+1){ // ----------------------------------------------------------
                        int cont = 0;

                        for(int e = 0; sp2[e] != '0' ; e++){ // conta as letras iguais
                            for(int h = 0; sp1[h] != '0' ; h++){
                                if(sp2[e] == sp1[h]){
                                    cont++;
                                    sp1[h] = '1';
                                    break;
                                }
                            }
                        }

                        if(cont==t1-1){
                            if(tootal_pares == 0){
                                printf("Pares de palavras vizinhas encontrados:\n");
                            }
                            for(int v=loc1; clonepalavras[v]!= ' ' && clonepalavras[v] != '\n' && clonepalavras[v] != '\000'; v++){
                                printf("%c", clonepalavras[v]);
                            }
                            printf(" e ");
                            for(int v=loc2; clonepalavras[v]!= ' ' && clonepalavras[v] != '\n' && clonepalavras[v] != '\000'; v++){
                                printf("%c", clonepalavras[v]);
                            }
                            printf("\n");
                            tootal_pares++;
                            
                        }

                    }else if(t2 == t1+1){ // ===============================================================
                        int cont = 0;

                        for(int e = 0; sp1[e] != '0' ; e++){ // conta as letras iguais
                            for(int h = 0; sp2[h] != '0' ; h++){
                                if(sp2[h] == sp1[e]){
                                    cont++;
                                    sp2[h] = '1';
                                }
                            }
                        }


                        if(cont==t1){
                            if(tootal_pares == 0){
                                printf("Pares de palavras vizinhas encontrados:\n");
                            }
                            for(int v=loc1; clonepalavras[v]!= ' ' && clonepalavras[v] != '\n' && clonepalavras[v] != '\000'; v++){
                                printf("%c", clonepalavras[v]);
                            }
                            printf(" e ");
                            for(int v=loc2; clonepalavras[v]!= ' ' && clonepalavras[v] != '\n' && clonepalavras[v] != '\000'; v++){
                                printf("%c", clonepalavras[v]);
                            }
                            printf("\n");
                            tootal_pares++;
                            
                        }

                    }
                    
                }
            }
        }else{
            break;
        }
    }

    

    if(tootal_pares == 0){
        printf("Nao existem palavras vizinhas na frase.\n");
    }else{
        printf("\nTotal de pares: %d\n", tootal_pares);
    }

    return 0;
}