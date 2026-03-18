#include <stdio.h>

int main(){
    char L;
    scanf("%c", &L);

    int x = L - 'A';

    for(int i = 'A'; i <= L; i++){

        if(x != 0){

            for(int j = 1; j <= x ; j++){
                printf(".");
            }

        }

        for(int j = 'A'; j <= i; j++){
            printf("%c", j);
        }

        for(int j = i-1 ; j >= 'A' ; j--){
            printf("%c", j);
        }

        if(x != 0){

            for(int j = 1; j <= x ; j++){
                printf(".");
            }
            
            x--;
        }

        printf("\n");
    }

    return 0;
}