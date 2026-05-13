#include <stdio.h>
#include <locale.h>
int main() {
    setlocale(LC_ALL, "portuguese");

    // informações baralho
    // Das 44 cartas do baralho, 26 são monstros (naipe preto), 9 armas (Ouro) e 9 poções (Copas)
    int baralho_total[44];
    int baralho_naipes[44]; 

    // informações player
    int hp = 0;

    if (hp <= 0)
    {
        printf("=========== Game Over! =========== \nVocê foi consumido pela masmorra \n");
    }
    
    return 0;
}