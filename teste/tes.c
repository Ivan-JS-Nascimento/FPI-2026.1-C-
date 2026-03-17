#include <stdio.h>

int main(){
    int q, x, colum=1, mais1 = 0;
    char y;

    scanf("%d", &q);

    for(int i = 0; i < q; i++){
        scanf("%d %c", &x, &y);

        switch (y){
        case 'D':
            if(colum == 1){
                for(int j = 0 ; j < x+mais1 ; j++){
                    printf(".");
                }

            }else{
                for(int j = 1 ; j < colum; j++){
                    printf(" ");
                }
                for(int j = 0 ; j < x+mais1 ; j++){
                    printf(".");
                }
                
            }
            colum += x+mais1-1;
            mais1 = 0;

            break;

        case 'B':
            if(colum == 1){
                for(int j = 0 ; j < x ; j++){
                    printf(".");
                    if( j < x-2){
                        printf("\n");
                    }
                }
                

            }else{
                for(int g = 0; g<x-1 ;g++){
                    for(int j = 1 ; j < colum ; j++){
                        printf(" ");
                    }
                    printf(".");
                    if( g != x-2 ){
                        printf("\n");
                    }
                    
                }
            }
            mais1 = 1;
            
            break;

        case 'E':   
            if(colum-x-mais1 < 1){
                printf("Informacao invalida");
            }else{
                if(colum-x-mais1 == 1){
                    for(int j = 0 ; j < x+mais1 ; j++){
                        printf(".");
                    }
                    
                }else{
                    for(int j = 0 ; j < colum-x-mais1 ; j++){
                        printf(" ");
                    }
                    for(int j = 0 ; j < x+mais1 ; j++){
                        printf(".");
                    }

                }

            }
            colum -= x;
            mais1 = 0;
            
            break;
        
        default:
            break;
        }

        if(x!=1 || y!='B'){
            if(i == q-1 && y=='B'){
                if(colum == 1){
                    printf(".");

                }else{
                    for(int j = 1 ; j < colum ; j++){
                        printf(" ");
                    }
                    printf(".");
                    
                }
            }else{
                printf("\n");
            }
        }
    }
    return 0;
}