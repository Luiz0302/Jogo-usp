#include <stdio.h>
#include <locale.h>
int main() {
    setlocale(LC_ALL, "portuguese");

    // informações baralho
    // Das 44 cartas do baralho, 26 são monstros (naipe preto), 9 armas (Ouro) e 9 poções (Copas)
    int baralho_total[44];
    int baralho_naipes[44]; 

    // informações player

    int hp = 20;
    int arma_equipada = 0;
    int limite_arma = 1;
    int skip_sala = 0;
    int pode_skip = 1;

    // informações mesa

    


    // --- Finalização do jogo ---
    if (hp <= 0)
    {
        printf("=========== Game Over! =========== \n Você foi consumido pela masmorra \n");
    }
    else
    {
        printf("=========== Parabéns! =========== \n Você derrotou a masmorra \n");
    }
    
    return 0;
}