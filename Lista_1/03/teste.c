#include <stdio.h>

int main(){
    int dinheiro, x, y, z;
    float dx, dy, dz, total, sobra;
    float rebeka = 3.0;
    float ganhou = 0.0;

    scanf("%d", &dinheiro);
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &z);

    dx = dinheiro * x / 100.0;
    dy = dinheiro * y / 100.0;
    dz = dinheiro * z / 100.0;

    int divisivel = ((int)dx == dx && (int)dy == dy && (int)dz == dz);
    sobra = dinheiro - (dx + dy + dz);

    if(divisivel){
        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", (int)dx, (int)dy, (int)dz);
        ganhou = sobra;

    } else {
        // Tenta com +1 real
        float tx = (dinheiro+1) * x / 100.0;
        float ty = (dinheiro+1) * y / 100.0;
        float tz = (dinheiro+1) * z / 100.0;
        sobra = (dinheiro+1) - (tx + ty + tz);
        int div1 = ((int)tx == tx && (int)ty == ty && (int)tz == tz);

        if(div1 && sobra >= 2){
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", (int)tx, (int)ty, (int)tz);
            rebeka -= 1;
            ganhou = sobra;

        } else {
            // Tenta com +2 reais
            tx = (dinheiro+2) * x / 100.0;
            ty = (dinheiro+2) * y / 100.0;
            tz = (dinheiro+2) * z / 100.0;
            sobra = (dinheiro+2) - (tx + ty + tz);
            int div2 = ((int)tx == tx && (int)ty == ty && (int)tz == tz);

            if(div2 && sobra >= 3){
                printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", (int)tx, (int)ty, (int)tz);
                rebeka -= 2;
                ganhou = sobra;

                char l1, l2, l3;
                scanf(" %c %c %c", &l1, &l2, &l3);
                int soma = (l1-'a'+1) + (l2-'a'+1) + (l3-'a'+1); // to levando em cosideracao que vao ser minusculas
                printf("%d\n", soma);

            } else {
                // Tenta com +3 reais
                tx = (dinheiro+3) * x / 100.0;
                ty = (dinheiro+3) * y / 100.0;
                tz = (dinheiro+3) * z / 100.0;
                sobra = (dinheiro+3) - (tx + ty + tz);
                int div3 = ((int)tx == tx && (int)ty == ty && (int)tz == tz);

                if(div3 && sobra >= 4){
                    printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", (int)tx, (int)ty, (int)tz);
                    rebeka -= 3;
                    ganhou = sobra;

                    int id1, id2, id3;
                    scanf("%d %d %d", &id1, &id2, &id3);
                    int temDiv3 = (id1%3==0 || id2%3==0 || id3%3==0);
                    if(temDiv3){
                        int parcelas = 0;
                        if(id1%3==0) parcelas += id1/3;
                        if(id2%3==0) parcelas += id2/3;
                        if(id3%3==0) parcelas += id3/3;
                        printf("%d\n", parcelas);
                    }

                } else {
                    printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
                }
            }
        }
    }

    float total_rebeka = rebeka + ganhou;
    if(total_rebeka >= 7){
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
    } else {
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }

    return 0;
}