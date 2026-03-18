#include <stdio.h>

/*
- Utilize ia para me exolicar uma logica que funcina, 
a partir das explicações da logica, fui escrevendo o codigo 
e perguntando em quais casos ainda dava problema.
*/

int main(){
    int N, K, P, primeironum = -1, Q = 0;
    scanf("%d %d %d", &N, &K, &P);

    for(int i = N ; i < K ; i++){
        int contagem = 0, valido = 0, d = 3, num = i, duplicata = 0;
        //printf("i = %d\n", i);
        
    //----------------------------
        //  0 e 1 nao tem divisores primos
        if(num <= 1){
            valido = 1;
        } else {
            // elimina fator 2 
            while (num % 2 == 0){
                num /= 2;
            }
            // testa divisores impares
            while ( d * d <= num ){
                //printf("num = %d\n", num);
                if( num % d == 0 ){
                    int vezes = 0;

                    //========================
                    // se aparece mais de uma vez o valor i ? invalido
                    while (num % d == 0){
                        vezes++;
                        num /= d;
                    }
                    if (vezes > 1){
                        duplicata = 1;
                        num = 0;
                        contagem = 0;
                        break;
                    }
                    //========================
                    contagem++;
                    //printf("divisor = %d\n", d);
                    
                }
                d+=2;
            }
            if (num>1){// essa parte ? tipo um else do while em casos tipo '7 / 7', '5 / 5'...
                contagem++;
            }

            if(!duplicata){
                valido = 1;
            }

        }
        //guarda o primeiro valido
        if (valido && contagem == P) {
            //printf("� valido\n");

            if (primeironum == -1) {
                //printf("primeiro valor\n");
                primeironum = i;
            } else {
                //printf("outro valor\n");
                //conta todos os v?lidos
                Q++;
            }
        }
        //printf("\n");
    //----------------------------
    }

    if (primeironum == -1) {    
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    } else {
        printf("%d %d\n", primeironum, Q);
    }

    return 0;
}