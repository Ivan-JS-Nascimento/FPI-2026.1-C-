#include <stdio.h>

int main(){
    int diaN, mesN, anoN, diaA, mesA, anoA;
    int amor, sorte, trabalho, cor;

    scanf("%d/%d/%d %d/%d/%d", &diaN, &mesN, &anoN, &diaA, &mesA, &anoA);

    // Amor

    amor = (diaN + mesN + anoN + diaA + mesA + anoA) * 7 % 101;

    printf("Amor: %d%% ", amor);
    if (amor < 20){
        puts("Pessimo dia para se apaixonar.");
    }
    else if ( amor <= 40){
        puts("Melhor manter o coracao <3 longe de perigo.");
    }
    else if (amor <= 69){
        puts("Se o papo e as ideias baterem, esta liberado pensar em algo.");
    }
    else if (amor <= 80){
        puts("Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.");
    }
    else{
        puts("Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.");
    } 
    

    // Sorte

    sorte = ((diaA + diaN + mesA + mesN) * 9 + (anoA - anoN)) % 101;
    printf("Sorte: %d%% ", sorte); 

    if (sorte < 30){
        printf("Nem jogue moedas pra cima hoje.");
    }
    else if ( sorte <= 50){
        printf("Melhor nao arriscar.");
    }
    else if (sorte <= 79){
        printf("Por sua conta em risco.");
    }
    else if (sorte <= 90){
        printf("Hoje vale a pena arriscar.");
    }
    else{
        printf("Nao tenha medo de virar cartas hoje.");
    }
    puts(" Sem tigrinho nem jogos de azar, por favor!");

    // Trabalho

    trabalho = (anoA + anoN - (diaA + diaN + mesA + mesN) * 8) % 101;

    printf("Trabalho: %d%% ",  trabalho);

    if (trabalho < 40){
        puts("Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.");
    }
    else if ( trabalho <= 50){
        puts("Segura a emocao, nao xinga ninguem, nao esquece de beber agua.");
    }
    else if (trabalho <= 69){
        puts("Um dia proveitoso com certeza, leve sua simpatia consigo.");
    }
    else if (trabalho <= 84){
        puts("Boas vibracoes hoje, chances podem estar ao seu redor.");
    }
    else if (trabalho > 85){
        puts("Use do maximo de networking possível hoje, dia bom para negocios.");
    }

    // Cor

    cor = (diaN*diaN + mesN*mesN + anoN*anoN + diaA*diaA + mesA*mesA + anoA*anoA) % 11;
    printf("%s","Cor: ");

    if (cor == 0){
        puts("Cinza.");
    }
    else if (cor == 1){
        puts("Vermelho.");
    }
    else if (cor == 2){
        puts("Laranja.");
    }
    else if (cor == 3){
        puts("Amarelo.");
    }
    else if (cor == 4){
        puts("Verde.");
    }
    else if (cor == 5){
        puts("Azul.");
    }
    else if (cor == 6){
        puts("Roxo.");
    }
    else if (cor == 7){
        puts("Marrom.");
    }
    else if (cor == 8){
        puts("Rosa.");
    }
    else if (cor == 9){
        puts("Preto.");
    }
    else if (cor == 10){
        puts("Branco.");
    }

    return 0;
}