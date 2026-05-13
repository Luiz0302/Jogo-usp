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

    // informações da mesa

    int mesa_ativa[4];
    int carta_valor[4];
    int carta_naipe[4];    

    printf("=========== Bem-vindo à Masmorra! =========== \n");
    printf("Sobreviva ás 10 salas ou sucumba tentando.\n");


    // Status do player

    printf("=========== Status do Player ===========\n");
    printf("HP: %d\n", hp);
    printf("Força da Arma Equipada: %d\n", arma_equipada); 
    printf("Limite de Armas: %d\n", limite_arma);
    printf("Pulo de sala: %d\n", pode_skip);

    
    
    
    // --- Finalização do jogo ---

    if (hp <= 0) // Tem que add condição de vitória, mas como não tem nada, vamo se virar com o hp
    {
        printf("========= Game Over! ========= \n Você foi consumido pela masmorra \n");
    }
    else
    {
        printf("=========== Parabéns! =========== \n Você derrotou a masmorra \n");
    }
    
    return 0;
}