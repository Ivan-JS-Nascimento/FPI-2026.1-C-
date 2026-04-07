#include <stdio.h>

int main() {
    int q;
    scanf("%d", &q);

    int coluna = 0, mais1 = 0;

    int i, j;
    for (i = 0; i < q; i++) {
        int x, h = 0;;
        char c;
        scanf("%d %c", &x, &c);

        switch (c) {
            case 'D':
                for (j = 0; j < coluna; j++) printf(" ");
                for (j = 0; j < x+mais1; j++) printf(".");
                printf("\n");
                coluna = coluna + x + mais1;
                mais1 = 0;
                break;

            case 'E':
                if (coluna - x - mais1 < 0) {
                    printf("Informacao invalida\n");
                    return 0;
                }
                for (j = 0; j < coluna - x - mais1; j++) printf(" ");
                for (j = 0; j < x+mais1; j++) printf(".");
                printf("\n");
                coluna = coluna - (x+mais1);
                mais1 = 0;
                break;

            case 'B':
                if (i == q-1){ 
                    h = 0;
                }else{
                    h = 1;
                }

                for (j = 0; j < x-h; j++) {
                    int k;
                    for (k = 0; k < coluna-1; k++) printf(" ");
                    if(coluna == 1) printf(" ");
                    printf(".\n");
                }
                mais1 = 1;
                break;
        }
    }

    return 0;
}