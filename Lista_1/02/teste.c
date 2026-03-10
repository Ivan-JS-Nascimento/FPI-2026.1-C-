#include <stdio.h>
int main(){
    long long N, A, B, soma;
    long long somaAteN, somaMultiploA, somaMultiploB, somaMultiploAB;
    
    scanf("%lld", &N);
    scanf("%lld %lld", &A, &B);
    
    long long AB = A * B;
    
    somaAteN     = N * (N + 1) / 2;
    somaMultiploA  = A * (N / A) * ((N / A) + 1) / 2;
    somaMultiploB  = B * (N / B) * ((N / B) + 1) / 2;
    somaMultiploAB = AB * (N / AB) * ((N / AB) + 1) / 2;
    
    soma = somaAteN - somaMultiploA - somaMultiploB + somaMultiploAB;
    
    printf("%lld\n", soma);
    if (soma % 2 == 0){
        puts("L� ele!!!");
    } else {
        puts("Opa xupenio AULAS...");
    }
    return 0;
}