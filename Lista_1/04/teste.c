#include <stdio.h>

int main(){
    int x, y, c;
    scanf("%d %d %d", &x, &y, &c);

    if(x > 0){ // direita

        if(y>0){ // cima

            if(c==1 || c==3){                                                //  
                puts("caminhada invalida");                                  // 
            }else if(c==2){                                                  // 
                printf("%d passos em y e %d passos em x", y+1, x+1);         //  #1
            }else{                                                           //
                printf("%d passos em x e %d passos em y", x+1, y+1);         //
            }                                                                //

        }else if(y<0){ // baixo

            if(c==2 || c==4){                                                //  
                puts("caminhada invalida");                                  // 
            }else if(c==1){                                                  // 
                printf("%d passos em x e %d passos em y", x+1, -y+1);        //  #4
            }else{                                                           //
                printf("%d passos em y e %d passos em x", -y+1, x+1);        //
            }                                                                //

        }

    }else if(x<0){ // esquerda

        if(y>0){ // cima                    

            if(c==4 || c==2){                                                //  
                puts("caminhada invalida");                                  // 
            }else if(c==3){                                                  // 
                printf("%d passos em x e %d passos em y", -x+1, y+1);        //  #2
            }else{                                                           //
                printf("%d passos em y e %d passos em x", y+1, -x+1);        //
            }                                                                //
        }else if(y<0){ // baixo   

            if(c==3 || c==1){                                                //  
                puts("caminhada invalida");                                  // 
            }else if(c==4){                                                  // 
                printf("%d passos em y e %d passos em x", -y+1, -x+1);       //  #3
            }else{                                                           //
                printf("%d passos em x e %d passos em y", -x+1, -y+1);       //
            }                                                                //

        }
    }
    return 0;
}